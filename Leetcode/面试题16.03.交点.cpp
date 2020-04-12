﻿//面试题16.03交点

//给定两条线段（表示为起点start = { X1, Y1 }和终点end = { X2, Y2 }），如果它们有交点，请计算其交点，没有交点则返回空值

//要求浮点型误差不超过10 ^ -6。若有多个交点（线段重叠）则返回 X 值最小的点，X 坐标相同则返回 Y 值最小的点

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    using Coor = vector <double>;
    static constexpr double EPS = 1E-6;

    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        int ax = start1[0], ay = start1[1], bx = end1[0], by = end1[1];
        int cx = start2[0], cy = start2[1], dx = end2[0], dy = end2[1];
        int acx = cx - ax, acy = cy - ay, abx = bx - ax, aby = by - ay, adx = dx - ax, ady = dy - ay;
        int cax = ax - cx, cay = ay - cy, cbx = bx - cx, cby = by - cy, cdx = dx - cx, cdy = dy - cy;
        // 叉积运算
        auto cross = [](int ux, int uy, int vx, int vy) {
            return ux * vy - vx * uy;
        };
        // 判断线段 (ux, uy) -- (vx, vy) 是否包含 (mx, my)  
        auto bothSide = [&](int mx, int my, int ux, int uy, int vx, int vy) {
            double um = sqrt((ux - mx) * (ux - mx) + (uy - my) * (uy - my));
            double vm = sqrt((vx - mx) * (vx - mx) + (vy - my) * (vy - my));
            double uv = sqrt((vx - ux) * (vx - ux) + (vy - uy) * (vy - uy));
            return (ux - mx) * (vx - mx) <= 0 && (uy - my) * (vy - my) <= 0;
        };
        // 以 x 为第一关键字，y 为第二关键字比较两个点的大小
        auto cmp = [](const Coor& u, const Coor& v) {
            if (u.size() == 0 || v.size() == 0) return v.size() == 0;
            return (u[0] != v[0]) ? (u[0] < v[0]) : (u[1] < v[1]);
        };
        // 共线处理
        if (cross(cax, cay, cbx, cby) == 0 || cross(adx, ady, abx, aby) == 0) {
            bool aInCd = bothSide(ax, ay, cx, cy, dx, dy), bInCd = bothSide(bx, by, cx, cy, dx, dy);
            bool cInAb = bothSide(cx, cy, ax, ay, bx, by), dInAb = bothSide(dx, dy, ax, ay, bx, by);
            Coor ans;
            if (aInCd) ans = min(ans, Coor({ (double)ax, (double)ay }), cmp);
            if (bInCd) ans = min(ans, Coor({ (double)bx, (double)by }), cmp);
            if (cInAb) ans = min(ans, Coor({ (double)cx, (double)cy }), cmp);
            if (dInAb) ans = min(ans, Coor({ (double)dx, (double)dy }), cmp);
            return ans;
        }
        // 判断两条线段是否有公共点
        auto intersect = [&]() {
            return cross(acx, acy, abx, aby) * cross(adx, ady, abx, aby) <= 0 && cross(cax, cay, cdx, cdy) * cross(cbx, cby, cdx, cdy) <= 0;
        };
        if (!intersect()) {
            return Coor();
        }
        // 计算三角形 PQM 的面积
        auto getArea = [&](int px, int py, int qx, int qy, int mx, int my) -> double {
            int mpx = px - mx, mpy = py - my, mqx = qx - mx, mqy = qy - my;
            return fabs(double(0.5) * cross(mpx, mpy, mqx, mqy));
        };
        // 定比分点
        double ck = getArea(ax, ay, bx, by, cx, cy), dk = getArea(ax, ay, bx, by, dx, dy);
        double k = ck / dk;
        double rx = (cx + k * dx) / (1 + k), ry = (cy + k * dy) / (1 + k);
        return Coor({ rx, ry });
    }
};

int main()
{
	return 0;
}