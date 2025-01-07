#include "clip.h"

namespace egc {

	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p) {
		std::vector<int> code;
        float minX = clipWindow.at(0).x, maxX = clipWindow.at(0).x, minY = clipWindow.at(0).y, maxY = clipWindow.at(0).y;
		for (const vec3& v : clipWindow) {
            if (v.x < minX) minX = v.x;
            if (v.x > maxX) maxX = v.x;
            if (v.y < minY) minY = v.y;
            if (v.y > maxY) maxY = v.y;
        }

        //TO DO - compute the code for the point given as argument
        //UDRL
        if (p.x < minX) code.push_back(1); else code.push_back(0);
        if (p.x > maxX) code.push_back(1); else code.push_back(0);
        if (p.y > maxY) code.push_back(1); else code.push_back(0);
        if (p.y < minY) code.push_back(1); else code.push_back(0);
		return code;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE REJECTION case
        for (int i = 0; i < 4; i++) {
            if (cod1.at(i) == cod2.at(i) && cod1.at(i) == 1) return true;
        }
        return false;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE ACCEPTANCE case
        for (int i = 0; i < 4; i++) {
            if (cod1.at(i) != 0) return false;
        }
        for (int i = 0; i < 4; i++) {
            if (cod2.at(i) != 0) return false;
        }
        return true;
	}

	//function returns -1 if the line segment cannot be clipped
	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		//TO DO - implement the Cohen-Sutherland line clipping algorithm - consult the laboratory work
        float minX = clipWindow[0].x, maxX = clipWindow[0].x;
        float minY = clipWindow[0].y, maxY = clipWindow[0].y;
        for (const vec3& v : clipWindow) {
            if (v.x < minX) minX = v.x;
            if (v.x > maxX) maxX = v.x;
            if (v.y < minY) minY = v.y;
            if (v.y > maxY) maxY = v.y;
        }

        std::vector<int> cod1 = computeCSCode(clipWindow, p1);
        std::vector<int> cod2 = computeCSCode(clipWindow, p2);

        while (true) {
            if (simpleAcceptance(cod1, cod2)) {
                return 0;
            } else if (simpleRejection(cod1, cod2)) {
                return -1;
            } else {
                float x,y;
                //0123
                //UDRL
                if (cod1.at(0) == 1) {
                    x = p1.x + (p2.x - p1.x) * (minY - p1.y) / (p2.y - p1.y);
                    y = minY;
                } else if (cod1.at(1) == 1) {
                    x = p1.x + (p2.x - p1.x) * (maxY - p1.y) / (p2.y - p1.y);
                    y = maxY;
                } else if (cod1.at(2) == 1) {
                    y = p1.y + (p2.y - p1.y) * (maxX - p1.x) / (p2.x - p1.x);
                    x = maxX;
                } else if (cod1.at(3) == 1) {
                    y = p1.y + (p2.y - p1.y) * (minX - p1.x) / (p2.x - p1.x);
                    x = minX;
                }

                p1.x = x;
                p1.y = y;

                cod1 = computeCSCode(clipWindow, p1);
                cod2 = computeCSCode(clipWindow, p2);


                if (cod1.at(0) == 0 && cod1.at(1) == 0 && cod1.at(2) == 0 && cod1.at(3) == 0) {
                    std::swap(p1, p2);
                    std::swap(cod1, cod2);
                }
            }
        }
	}
}

