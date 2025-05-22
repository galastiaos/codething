#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>  // File existence check
#include <cstdlib>  // system() calls

const int WIDTH = 800;
const int HEIGHT = 600;
const int FRAME_RATE = 30;
const int FRAME_COUNT = 100;
;
// Check if a file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Generate animation frames
void generateFrames() {
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Red);

    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        sf::RenderTexture texture;
        texture.create(WIDTH, HEIGHT);
        texture.clear(sf::Color::Black);

        // Move the circle across the screen
        shape.setPosition(frame * (WIDTH / FRAME_COUNT), HEIGHT / 2 - 50);
        texture.draw(shape);
        texture.display();

        sf::Image image = texture.getTexture().copyToImage();
        std::ostringstream filename; //the filename for the frame
        filename << "frame_" << frame << ".png"; //frame_01,frame_02,etc..
        image.saveToFile(filename.str());
    }
}

// Create a video (with or without audio)
void createVideo() {
    system("ffmpeg -framerate 30 -i frame_%d.png -c:v libx264 -pix_fmt yuv420p output.mp4");//turn all the image files into just video

    if (fileExists("audio.mp3")) {//audio for the video
        system("ffmpeg -i output.mp4 -i audio.mp3 -c:v copy -c:a aac -strict experimental final_video.mp4");//link the video with the audio into the final video
    } else {
        system("cp output.mp4 final_video.mp4");  // Use `cp` instead of `mv` to prevent weird errors
    }
}

// Play the final video
void playVideo() {
    system("mpv final_video.mp4");
}

int main() {
    generateFrames();
    createVideo();
    playVideo();
    return 0;
}

