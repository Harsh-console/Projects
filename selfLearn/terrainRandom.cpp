// smooth_moving_terrain.cpp
// Smoothly animated terrain in terminal using continuous noise scrolling
// Compile: g++ -std=c++17 smooth_moving_terrain.cpp -O2 -o terrain
// Run: ./terrain

#include <bits/stdc++.h>
#include <chrono>
#include <thread>
using namespace std;

static double fade(double t){ return t*t*t*(t*(t*6-15)+10); } // Perlin fade curve

// Simple 1D value noise with continuous offset
vector<double> generateHeightMap(int width, unsigned int seed, double offset, double roughness = 0.5, int octaves = 5){
    static vector<double> baseNoise;
    static bool initialized = false;
    if(!initialized){
        mt19937 rng(seed);
        uniform_real_distribution<double> ud(-1.0, 1.0);
        baseNoise.resize(2048);
        for(double &v : baseNoise) v = ud(rng);
        initialized = true;
    }

    vector<double> height(width, 0.0);
    double amplitude = 1.0, totalAmp = 0.0;

    for(int octave=0; octave<octaves; ++octave){
        int period = 1 << octave;
        double freq = 1.0 / period;
        for(int x=0;x<width;++x){
            double fx = (x + offset) * freq;
            int i0 = int(floor(fx)) % baseNoise.size();
            int i1 = (i0 + 1) % baseNoise.size();
            double t = fx - floor(fx);
            double s = fade(t);
            double val = baseNoise[i0]*(1.0 - s) + baseNoise[i1]*s;
            height[x] += val * amplitude;
        }
        totalAmp += amplitude;
        amplitude *= roughness;
    }

    double minv = *min_element(height.begin(), height.end());
    double maxv = *max_element(height.begin(), height.end());
    for(double &v : height) v = (v - minv) / (maxv - minv + 1e-9);
    return height;
}

char heightToChar(double h){
    static const string grad = " .,:;irsXA253hMH#W&8%$@";
    int idx = int(h * (grad.size() - 1));
    return grad[idx];
}

string colorForHeight(double h){
    int r,g,b;
    if(h < 0.35){ double t=h/0.35; r=80+40*t; g=40+140*t; b=20+20*t; }
    else if(h < 0.7){ double t=(h-0.35)/0.35; r=120+80*t; g=180-100*t; b=50+30*t; }
    else { double t=(h-0.7)/0.3; r=200+55*t; g=170+80*t; b=140+115*t; }
    char buf[32]; sprintf(buf,"\x1b[38;2;%d;%d;%dm",r,g,b);
    return string(buf);
}

int main(){
    ios::sync_with_stdio(false);
    cout << "\x1b[2J\x1b[?25l"; // Clear screen and hide cursor

    int width = 120, height = 30;
    unsigned int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    double roughness = 0.55;
    int octaves = 6;
    bool useColor = true;

    double offset = 0.0;
    const double speed = 0.6; // higher = faster scroll

    while(true){
        auto hm = generateHeightMap(width, seed, offset, roughness, octaves);
        vector<string> screen(height, string(width, ' '));
        for(int x=0;x<width;++x){
            int groundY = int((1.0 - hm[x]) * (height - 1));
            for(int y=groundY;y<height;++y){
                if(y==groundY) screen[y][x] = heightToChar(hm[x]);
                else screen[y][x] = '#';
            }
        }

        cout << "\x1b[H"; // Move cursor to top
        for(int y=0;y<height;++y){
            for(int x=0;x<width;++x){
                char ch = screen[y][x];
                if(ch==' '){ cout<<' '; continue; }
                if(ch=='#'){
                    if(useColor) cout << "\x1b[38;2;80;80;80m" << ch << "\x1b[0m";
                    else cout << ch;
                } else {
                    if(useColor) cout << colorForHeight(hm[x]) << ch << "\x1b[0m";
                    else cout << ch;
                }
            }
            cout << '\n';
        }
        cout.flush();

        offset += speed;
        this_thread::sleep_for(chrono::milliseconds(50)); // smoother animation
    }

    cout << "\x1b[?25h"; // show cursor again
}

