#include "Sculptor.h"
#include <iostream>
#include <fstream>

Sculptor::Sculptor(int _nx, int _ny, int _nz) : nx(_nx), ny(_ny), nz(_nz) {
    // aloca matriz 3d
    v = new Voxel * *[nx];
    for (int i = 0; i < nx; i++) {
        v[i] = new Voxel * [ny];
        for (int j = 0; j < ny; j++) {
            v[i][j] = new Voxel[nz];
            for (int k = 0; k < nz; k++) {
                v[i][j][k].isOn = false;
            }
        }
    }
}

Sculptor::~Sculptor() {
    // libera espaço utilizado pela matriz
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v;
}

void Sculptor::setColor(float r, float g, float b, float alpha) { 
    this->r = r; //quantidade de vermelho
    this->g = g; //quantidade de verde
    this->b = b; //quantidade de azul
    this->a = alpha; //opacidade
}

void Sculptor::putVoxel(int x, int y, int z) {
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].isOn = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

void Sculptor::cutVoxel(int x, int y, int z) {
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].isOn = false;
    }
}

void Sculptor::writeOFF(const char* filename) {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return;
    }

    // conta número de vox ligadas
    int num_voxels = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].isOn) {
                    num_voxels++;
                }
            }
        }
    }

    // cabeçalho
    ofs << "OFF\n";
    ofs << 8 * num_voxels << " " << 6 * num_voxels << " 0\n";

    // vertices e faces
    int vertexIndex = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].isOn) {
                    float x = i - 0.5f;
                    float y = j - 0.5f;
                    float z = k - 0.5f;
                    float x1 = i + 0.5f;
                    float y1 = j + 0.5f;
                    float z1 = k + 0.5f;
                    ofs << x << " " << y << " " << z << "\n";
                    ofs << x1 << " " << y << " " << z << "\n";
                    ofs << x1 << " " << y1 << " " << z << "\n";
                    ofs << x << " " << y1 << " " << z << "\n";
                    ofs << x << " " << y << " " << z1 << "\n";
                    ofs << x1 << " " << y << " " << z1 << "\n";
                    ofs << x1 << " " << y1 << " " << z1 << "\n";
                    ofs << x << " " << y1 << " " << z1 << "\n";

                    int idx = vertexIndex * 8;
                    ofs << "4 " << idx << " " << idx + 1 << " " << idx + 2 << " " << idx + 3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    ofs << "4 " << idx + 4 << " " << idx + 5 << " " << idx + 6 << " " << idx + 7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    ofs << "4 " << idx << " " << idx + 1 << " " << idx + 5 << " " << idx + 4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    ofs << "4 " << idx << " " << idx + 3 << " " << idx + 7 << " " << idx + 4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    ofs << "4 " << idx + 3 << " " << idx + 2 << " " << idx + 6 << " " << idx + 7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    ofs << "4 " << idx + 1 << " " << idx + 2 << " " << idx + 6 << " " << idx + 5 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";

                    vertexIndex++;
                }
            }
        }
    }

    ofs.close();
}
