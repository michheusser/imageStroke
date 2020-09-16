#include <iostream>
#include <typeinfo>
#include <cmath>

using namespace std;

class ImageGrid {
public:
    ImageGrid() {
        xFields = 1;
        yFields = 1;
        gridArray = new bool[1];
        gridArray[0] = false;
    }

    ImageGrid(const bool* gA, const unsigned int xF, const unsigned int yF) {
        xFields = xF;
        yFields = yF;
        gridArray = new bool[xFields * yFields];
        for (unsigned int y = 0; y < yFields; ++y) {
            for (unsigned int x = 0; x < yFields; ++x) {
                gridArray[y * xFields + x] = gA[y * xFields + x];
            }
        }
    }

    /*ImageGrid(bool array2D, const unsigned int xF, const unsigned int yF) {
        xFields = xF;
        yFields = yF;
        gridArray = new bool[xFields * yFields];
        for (unsigned int y = 0; y < yFields; ++y) {
            for (unsigned int x = 0; x < yFields; ++x) {
                gridArray[y * xFields + x] = array2D[y][x];
            }
        }
    }*/

    ImageGrid(bool** array2D, const unsigned int xF, const unsigned int yF) {
        xFields = xF;
        yFields = yF;
        gridArray = new bool[xFields * yFields];
        for (unsigned int y = 0; y < yFields; ++y) {
            for (unsigned int x = 0; x < yFields; ++x) {
                gridArray[y * xFields + x] = array2D[y][x];
            }
        }
    }

    ~ImageGrid() {
        delete[] gridArray;
    }

    void display() const {
        cout << "********  Grid  ************" << endl;
        for (unsigned int y = 0; y < yFields; ++y) {
            for (unsigned int x = 0; x < xFields; ++x) {
                cout << gridArray[y * xFields + x];
            }
            cout << endl;
        }
    }

    void scaleStroke(const unsigned int xFieldsScaled, const unsigned int yFieldsScaled) {
        bool* scaledData = new bool[xFieldsScaled * yFieldsScaled];
        for (unsigned int y = 0; y < yFieldsScaled; ++y) {
            for (unsigned int x = 0; x < xFieldsScaled; ++x) {
                scaledData[y * xFieldsScaled + x] = false;
            }

            const int xFieldsAugmented = xFields != 1 ? ceil(1.0 * (xFieldsScaled - 1) * xFields / (xFields - 1)) : 0;
            const int yFieldsAugmented = yFields != 1 ? ceil(1.0 * (yFieldsScaled - 1) * yFields / (yFields - 1)) : 0;

            const double scalingX = 1.0 * xFieldsAugmented / xFields;
            const double scalingY = 1.0 * yFieldsAugmented / yFields;

            const int positions[5][2] = {{-1, 1},
                                         {0,  1},
                                         {1,  1},
                                         {1,  0},
                                         {-1, -1}};

            for (unsigned int y = 0; y < yFields; ++y) {
                for (unsigned int x = 0; x < xFields; ++x) {
                    if (gridArray[y * xFields + x]) {
                        const int xScaled = x * scalingX;
                        const int yScaled = y * scalingY;
                        scaledData[yScaled * xFieldsScaled + xScaled] = true;
                        for (unsigned int i = 0; i < 5; ++i) {
                            const int xNext =
                                    0 <= x + positions[i][1] && x + positions[i][1] < xFields ? x + positions[i][1] : x;
                            const int yNext =
                                    0 <= y + positions[i][0] && y + positions[i][0] < yFields ? y + positions[i][0] : y;
                            if (gridArray[yNext * xFields + xNext] &&
                                !(isCorner(x, y, positions[i]))) {
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
        }
        delete[] gridArray;
        gridArray = scaledData;
        xFields = xFieldsScaled;
        yFields = yFieldsScaled;
    }

private:
    unsigned int xFields;
    unsigned int yFields;
    bool* gridArray;

    bool isCorner(const int x, const int y, const int position[]) {
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
    }
};


int main() {
    const unsigned int xFields = 4;
    const unsigned int yFields = 3;
    const unsigned int xFieldsScaled = 50;
    const unsigned int yFieldsScaled = 40;

    // Statically defined 1D:
    const bool dataStatic[
            xFields * yFields] {true, true, true, false, true, true, true, false, true, true, true, false};

    /*ImageGrid imageGrid(dataStatic, xFields, yFields);
    imageGrid.display();
    imageGrid.scaleStroke(xFieldsScaled, yFieldsScaled);
    imageGrid.display();*/

    // Dinamically defined 1D:
    bool* dataDynamic = new bool[xFields*yFields];
    for(unsigned int y = 0; y<yFields; ++y){
        for(unsigned int x = 0; x<xFields; ++x){
            dataDynamic[y*xFields + x] = dataStatic[y*xFields + x];
        }
    }
    /*ImageGrid imageGrid(dataDynamic, xFields, yFields);
    imageGrid.display();
    imageGrid.scaleStroke(xFieldsScaled, yFieldsScaled);
    imageGrid.display();*/

    // Statically defined 2D:
    const bool dataStatic2D[yFields][xFields] = {{true, true, true, false},{true, true, true, false},{true, true, true, false}};
    ImageGrid imageGrid(dataStatic2D, xFields, yFields);
    imageGrid.display();
    imageGrid.scaleStroke(xFieldsScaled, yFieldsScaled);
    imageGrid.display();

    // Dynamically defined 2D:
    bool** dataDynamic2D = new bool*[yFields];
    for(unsigned int y = 0; y<yFields; ++y){
        dataDynamic2D[y] = new bool[xFields];
        for(unsigned int x = 0; x<xFields; ++x){
            dataDynamic2D[y][x] = dataStatic[y*xFields + x];
        }
    }
    /*ImageGrid imageGrid(dataDynamic2D, xFields, yFields);
    imageGrid.display();
    imageGrid.scaleStroke(xFieldsScaled, yFieldsScaled);
    imageGrid.display();/*

    //const bool data2D** = new bool*[xFields];
}