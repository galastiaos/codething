#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>

const int WIDTH = 800;
const int HEIGHT = 600;
const int TOTAL_FRAMES = 10; // Number of keyframes in the timeline
const int SHAPE_RADIUS = 30;

// Simple structure to store per-frame data
struct FrameData {
    sf::Vector2f pos;
};

// Check if a file exists
bool fileExists(const std::string &filename) {
    std::ifstream file(filename);
    return file.good();
}

// Save a rendered frame to a file (used during export)
void saveExportFrame(const sf::RenderTexture &texture, int frame) {
    sf::Image image = texture.getTexture().copyToImage();
    std::ostringstream filename;
    filename << "export_frame_" << frame << ".png";
    image.saveToFile(filename.str());
}

// Function to export the current timeline to a video with optional audio
void exportAnimation(const std::vector<FrameData> &timeline) {
    // Render each timeline frame off-screen
    for (size_t i = 0; i < timeline.size(); i++) {
        sf::RenderTexture texture;
        if (!texture.create(WIDTH, HEIGHT)) {
            std::cerr << "Failed to create render texture for frame " << i << "\n";
            return;
        }
        texture.clear(sf::Color::Black);
        
        sf::CircleShape shape(SHAPE_RADIUS);
        shape.setOrigin(SHAPE_RADIUS, SHAPE_RADIUS);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(timeline[i].pos);
        texture.draw(shape);
        texture.display();
        
        saveExportFrame(texture, i);
    }
    
    // Create video from exported frames (assumes frame names export_frame_0.png, export_frame_1.png, etc.)
    // Adjust framerate (-framerate 30) and resolution as needed.
    system("ffmpeg -y -framerate 30 -i export_frame_%d.png -c:v libx264 -pix_fmt yuv420p output.mp4");
    
    // Merge audio if available; if not, simply copy the video.
    if (fileExists("audio.mp3")) {
        system("ffmpeg -y -i output.mp4 -i audio.mp3 -c:v copy -c:a aac -strict experimental final_video.mp4");
    } else {
        system("cp output.mp4 final_video.mp4");
    }
    
    // Optionally, automatically play the video using mpv.
    system("mpv final_video.mp4");
}

// Main interactive drag & drop editor function
int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Drag & Drop Editor");
    window.setFramerateLimit(60);

    // Initialize timeline: each frame stores the position of the object (default to center)
    std::vector<FrameData> timeline(TOTAL_FRAMES, { { WIDTH / 2.f, HEIGHT / 2.f } });
    int currentFrame = 0;

    // Draggable object: a circle shape
    sf::CircleShape shape(SHAPE_RADIUS);
    shape.setOrigin(SHAPE_RADIUS, SHAPE_RADIUS);
    shape.setFillColor(sf::Color::Red);

    bool dragging = false;
    sf::Vector2f dragOffset;

    std::cout << "Instructions:\n"
              << " - Drag the red circle with the mouse to change its position for the current frame.\n"
              << " - Use Left/Right arrow keys to navigate frames.\n"
              << " - Press L to snap to left corner; R to snap to right corner (keeping current y).\n"
              << " - Press E to export the animation to video (with MP3 audio if available).\n";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window event
            if (event.type == sf::Event::Closed)
                window.close();

            // Mouse press: start dragging if clicking inside the circle
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                shape.setPosition(timeline[currentFrame].pos);
                if (shape.getGlobalBounds().contains(mousePos)) {
                    dragging = true;
                    dragOffset = timeline[currentFrame].pos - mousePos;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                dragging = false;
            if (event.type == sf::Event::MouseMoved && dragging) {
                sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                timeline[currentFrame].pos = mousePos + dragOffset;
            }

            // Keyboard input for frame navigation and macros
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right)
                    currentFrame = std::min(currentFrame + 1, TOTAL_FRAMES - 1);
                else if (event.key.code == sf::Keyboard::Left)
                    currentFrame = std::max(currentFrame - 1, 0);
                else if (event.key.code == sf::Keyboard::L)
                    timeline[currentFrame].pos.x = SHAPE_RADIUS; // Snap to left corner (x = radius)
                else if (event.key.code == sf::Keyboard::R)
                    timeline[currentFrame].pos.x = WIDTH - SHAPE_RADIUS; // Snap to right corner
                else if (event.key.code == sf::Keyboard::E) {
                    // Trigger export of the timeline to video
                    std::cout << "Exporting animation...\n";
                    exportAnimation(timeline);
                }
            }
        }

        window.clear(sf::Color::Black);

        // Onion skinning: draw previous frame (if exists) semi-transparently
        if (currentFrame > 0) {
            sf::CircleShape prevShape = shape;
            prevShape.setPosition(timeline[currentFrame - 1].pos);
            prevShape.setFillColor(sf::Color(255, 255, 255, 100));
            window.draw(prevShape);
        }
        // Onion skinning: draw next frame (if exists) semi-transparently
        if (currentFrame < TOTAL_FRAMES - 1) {
            sf::CircleShape nextShape = shape;
            nextShape.setPosition(timeline[currentFrame + 1].pos);
            nextShape.setFillColor(sf::Color(255, 255, 255, 100));
            window.draw(nextShape);
        }

        // Draw current frame object
        shape.setPosition(timeline[currentFrame].pos);
        shape.setFillColor(sf::Color::Red);
        window.draw(shape);

        window.display();
    }

    return 0;
}

