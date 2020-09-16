#include <iostream>
#include <typeinfo>
#include <cmath>

using namespace std;

class ImageGrid {
public:
    unsigned int xFields;
    unsigned int yFields;
    bool* gridArray;
    ImageGrid(){
        xFields = 1;
        yFields = 1;
        gridArray = new bool[1];
        gridArray[0] = false;
    }
    ImageGrid(const bool gA[], unsigned const int xF, unsigned const int yF){
        xFields = xF;
        yFields = yF;
        gridArray = new bool[xFields*yFields];
        for(unsigned int y=0; y<yFields; ++y){
            for(unsigned int x=0; x<yFields; ++x){
                gridArray[y*xFields + x] = gA[y*xFields+x];
            }
        }
    }
    ~ImageGrid(){
        delete[] gridArray;
    }
    void display(){
        cout << "********  Grid  ************" << endl;
        for (unsigned int y = 0; y < yFields; ++y) {
            for (unsigned int x = 0; x < xFields; ++x) {
                cout << gridArray[y * xFields + x];
            }
            cout << endl;
        }
        return;
    }

private:

};


/*bool isCorner(const bool gridArray[], const int xFields, const int yFields, const int x, const int y,
              const int position[]) {
    const int positionC[2] = {(position[0] - position[1]) / 2, (position[0] + position[1]) / 2};
    const int positionCC[2] = {(position[1] + position[0]) / 2, (position[1] - position[0]) / 2};
    const int xNextC = x + positionC[1];
    const int yNextC = y + positionC[0];
    const int xNextCC = x + positionCC[1];
    const int yNextCC = y + positionCC[0];
    if ((abs(position[0]) == 1 && abs(position[1]) == 1) &&
        (0 <= xNextC && xNextC < xFields && 0 <= yNextC && yNextC < yFields &&
         0 <= xNextCC && xNextCC < xFields && 0 <= yNextCC && yNextCC < yFields)) {
        if (gridArray[y * xFields + x] &&
            (gridArray[yNextC * xFields + xNextC] || gridArray[yNextCC * xFields + xNextCC])) {
            return true;
        }
    }
    return false;
}*/

int main() {
    const unsigned int xFields = 4;
    const unsigned int yFields = 3;
    const unsigned int xFieldsScaled = 50;
    const unsigned int yFieldsScaled = 40;

    const bool data[
            xFields * yFields] = {true, true, true, false, true, true, true, false, true, true, true, false};

    ImageGrid imageGrid(data,xFields,yFields);
    imageGrid.display();
    /*bool scaledData[xFieldsScaled * yFieldsScaled] = {};

    const int xFieldsAugmented = xFields != 1 ? ceil(1.0 * (xFieldsScaled - 1) * xFields / (xFields - 1)) : 0;
    const int yFieldsAugmented = yFields != 1 ? ceil(1.0 * (yFieldsScaled - 1) * yFields / (yFields - 1)) : 0;

    const double scalingX = xFieldsAugmented / xFields;
    const double scalingY = yFieldsAugmented / yFields;

    const int positions[5][2] = {{-1, 1},
                                 {0,  1},
                                 {1,  1},
                                 {1,  0},
                                 {-1, -1}};

    for (unsigned int y = 0; y < yFields; ++y) {
        for (unsigned int x = 0; x < xFields; ++x) {
            if (data[y * xFields + x]) {
                const int xScaled = x * scalingX;
                const int yScaled = y * scalingY;
                scaledData[yScaled * xFieldsScaled + xScaled] = true;
                for (unsigned int i = 0; i < 5; ++i) {
                    const int xNext =
                            0 <= x + positions[i][1] && x + positions[i][1] < xFields ? x + positions[i][1] : x;
                    const int yNext =
                            0 <= y + positions[i][0] && y + positions[i][0] < yFields ? y + positions[i][0] : y;
                    if (data[yNext * xFields + xNext] && !(isCorner(data, xFields, yFields, x, y, positions[i]))) {
                        const int xScaledNext = xNext * scalingX;
                        const int yScaledNext = yNext * scalingY;
                        const int tMax = max(abs(xScaledNext - xScaled), abs(yScaledNext - yScaled));
                        for (unsigned int t = 1; t < tMax; ++t) {
                            const int xP = xScaled + (1.0 * t / tMax) * (xScaledNext - xScaled);
                            const int yP = yScaled + (1.0 * t / tMax) * (yScaledNext - yScaled);
                            scaledData[yP * xFieldsScaled + xP] = true;
                        }
                    }
                }
            }
        }
    }

    displayGrid(data, xFields, yFields);
    displayGrid(scaledData, xFieldsScaled, yFieldsScaled);
    return 0;*/
}