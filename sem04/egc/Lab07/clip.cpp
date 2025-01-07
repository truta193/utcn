#include "clip.h"

namespace egc {

	//Cyrus-Beck clipping algorithm
	//clipWindow specifies the vertices that define the clipping area in conterclockwise order
	//and can represent any convex polygon
	//function returns -1 if the line segment cannot be clipped
	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
        std::vector<vec3> normal;
        for (int i = 0; i < clipWindow.size(); i++) {
            vec3 edge = clipWindow[(i + 1) % clipWindow.size()] - clipWindow[i];
            normal.push_back(vec3(-edge.y, edge.x, 0.0f));
        }

        if (p1 == p2) {
            return -1;
        }

        float t_enter = 0.0f;
        float t_leave = 1.0f;

        for (int i = 0; i < clipWindow.size(); i++) {
            vec3 n = normal.at(i);
            vec3 w = p1 - clipWindow[i];
            float n_dot_w = dotProduct(n, w);
            float n_dot_d = dotProduct(n, p2 - p1);

            float t = -n_dot_w / n_dot_d;

            if (n_dot_d < 0) {
                if (t > t_enter) {
                    std::cout << "tenter " << t << std::endl;
                    t_enter = t;
                }
            }
            else {
                if (t < t_leave) {
                    std::cout << "tleave " << t << std::endl;

                    t_leave = t;
                }
            }


        }

        if (t_enter > t_leave)
            return -1;

        vec3 clipped_p1 = p1 + (p2 - p1) * t_enter;
        vec3 clipped_p2 = p1 + (p2 - p1) * t_leave;

        p1 = clipped_p1;
        p2 = clipped_p2;

        return 0;

		return 0;
	}

	
}

