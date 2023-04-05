#pragma once

class Point2D {
public:
	Point2D(int y, int x);
	~Point2D() = default;

	void move(int dy, int dx);
	void set(int ny, int nx);

	void setY(int ny);
	void setX(int nx);

	int y();
	int x();

private:
	int m_y, m_x;
};
