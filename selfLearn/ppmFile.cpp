#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int width = 256, height = 256;
    ofstream img("output.ppm");
    img << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int r = x % 256;
            int g = y % 256;
            int b = (x + y) % 256;
            img << r << " " << g << " " << b << " ";
        }
        img << "\n";
    }

    img.close();
    cout << "Saved as output.ppm\n";
}
