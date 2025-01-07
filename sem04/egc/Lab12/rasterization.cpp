#include "rasterization.h"

namespace egc {


    void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma)
    {
        vec2 v0 = vec2(triangleVertices[0].x, triangleVertices[0].y);
        vec2 v1 = vec2(triangleVertices[1].x, triangleVertices[1].y);
        vec2 v2 = vec2(triangleVertices[2].x, triangleVertices[2].y);

        float denom = (v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y);
        alpha = ((v1.y - v2.y) * (pixel.x - v2.x) + (v2.x - v1.x) * (pixel.y - v2.y)) / denom;
        beta = ((v2.y - v0.y) * (pixel.x - v2.x) + (v0.x - v2.x) * (pixel.y - v2.y)) / denom;
        gamma = 1.0f - alpha - beta;
    }

    void rasterizeTriangle(SDL_Renderer *renderer, const std::vector<egc::vec4> &triangleVertices, const std::vector<egc::vec4> &triangleColors) {
        // Determine the bounding box of the triangle
        int minX = std::min(triangleVertices[0].x, std::min(triangleVertices[1].x, triangleVertices[2].x));
        int minY = std::min(triangleVertices[0].y, std::min(triangleVertices[1].y, triangleVertices[2].y));
        int maxX = std::max(triangleVertices[0].x, std::max(triangleVertices[1].x, triangleVertices[2].x));
        int maxY = std::max(triangleVertices[0].y, std::max(triangleVertices[1].y, triangleVertices[2].y));

        for (int y = minY; y <= maxY; y++) {
            for (int x = minX; x <= maxX; x++) {
                vec2 pixel(x, y);
                float alpha, beta, gamma;
                computeAlphaBetaGamma(triangleVertices, pixel, alpha, beta, gamma);

                // Check if the pixel is inside the triangle
                if (alpha >= 0 && beta >= 0 && gamma >= 0 && alpha <= 1 && beta <= 1 && gamma <= 1) {
                    // Interpolate the color of the pixel using barycentric coordinates
                    float r = alpha * triangleColors[0].r + beta * triangleColors[1].r + gamma * triangleColors[2].r;
                    float g = alpha * triangleColors[0].g + beta * triangleColors[1].g + gamma * triangleColors[2].g;
                    float b = alpha * triangleColors[0].b + beta * triangleColors[1].b + gamma * triangleColors[2].b;

                    SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(r * 255), static_cast<Uint8>(g * 255), static_cast<Uint8>(b * 255), 255);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }
    }


}