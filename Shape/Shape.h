#pragma once

/// ===================================================
/// 
/// ===================================================
class IShape {
public:
	/// ===================================================
	/// public : methods
	/// ===================================================
	virtual ~IShape() = default;

	virtual void Size() = 0;
	virtual void Draw() = 0;

protected:
	float size_;
};


class Circle : public IShape {
public:
	Circle(float _radius) : radius_(_radius) {}
	~Circle() {}

	void Size() override;
	void Draw() override;
private:
	float radius_;
};


class Rectangle : public IShape {
public:
	Rectangle(float _wight, float _height) : width_(_wight), height_(_height) {}
	~Rectangle() {}

	void Size() override;
	void Draw() override;
private:
	float width_;
	float height_;
};