/*
 * File:   collision.cpp
 * Author: Nick (original version), ahnonay (SFML2 compatibility)
 */
#include <SFML/Graphics.hpp>
#include <map>
#include <math.h>
#include "Collision.h"
#include <iostream>
#define eps 1e-9
sf::RectangleShape temp1;
sf::RectangleShape temp2;
int cmp(float a, float b) {
	if (abs(a - b) < eps) return 0;
	return (a > b ? 1 : -1);
}

int ccw(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2) {
	float dx1 = p1.x - p0.x;               
	float dy1 = p1.y - p0.y;
	float dx2 = p2.x - p0.x;
	float dy2 = p2.y - p0.y;
	return cmp(dx1 * dy2 - dx2 * dy1, 0.f);
}

int insidePolygon(std::vector<sf::Vector2f> P, int n, sf::Vector2f p0) {
	P.push_back(P[0]);
	int x1 = 0, x2 = 0;
	for(int i = 0; i< n; i++) {
		if (ccw(P[i], P[i + 1], p0) == 0) return 0;
		else if (ccw(P[i], P[i + 1], p0) == -1) x1++;
		else x2++;
	}
	return (!x1 || !x2);
}

bool lineintercircle(sf::CircleShape* Object1, sf::Vector2f point, sf::Vector2f point1, std::vector<float> P) {
	if (cmp(P[1], 0.f) == 0) {
		float temp = Object1->getRadius() * Object1->getRadius() - (point.x - Object1->getPosition().x) * (point.x - Object1->getPosition().x);
		if (cmp(temp, 0.f) != -1)
		{
			if ((Object1->getPosition().y - sqrt(temp) >= std::min(point.y, point1.y) && Object1->getPosition().y - sqrt(temp) <= std::max(point.y, point1.y)) ||
				(Object1->getPosition().y + sqrt(temp) >= std::min(point.y, point1.y) && Object1->getPosition().y + sqrt(temp) <= std::max(point.y, point1.y)))
				return true;
		}
	}
	else {
		float temp = (P[2] / P[1] + Object1->getPosition().y) * (P[0] / P[1]) - Object1->getPosition().x;
		float temp1 = ((P[2] / P[1] + Object1->getPosition().y) * (P[2] / P[1] + Object1->getPosition().y) + Object1->getPosition().x * Object1->getPosition().x);
		float temp2 = (P[0] * P[0]) / (P[1] * P[1]) + 1;
		float temp3 = temp * temp - temp1 * temp2;
		if (cmp(temp3, 0.f) != -1)
		{
			float x1 = (-temp - sqrt(temp3)) / temp2;
			float y1 = (-P[2] - P[0] * x1) / P[1];
			float x2 = (-temp + sqrt(temp3)) / temp2;
			float y2 = (-P[2] - P[0] * x1) / P[1];
			if ((x1 >= std::min(point.x, point1.x) && x1 <= std::min(point.x, point1.x) && y1 >= std::min(point.y, point1.y) && y1 <= std::min(point.y, point1.y)) ||
				(x2 >= std::min(point.x, point1.x) && x2 <= std::min(point.x, point1.x) && y2 >= std::min(point.y, point1.y) && y2 <= std::min(point.y, point1.y)) )
			return true;
		}
	}
	return false;
}


namespace Collision
{
	class BitmaskManager
	{
	public:
		~BitmaskManager() {
			std::map<const sf::Texture*, sf::Uint8*>::const_iterator end = Bitmasks.end();
			for (std::map<const sf::Texture*, sf::Uint8*>::const_iterator iter = Bitmasks.begin(); iter != end; iter++)
				delete[] iter->second;
		}

		sf::Uint8 GetPixel(const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
			if (x > tex->getSize().x || y > tex->getSize().y)
				return 0;

			return mask[x + y * tex->getSize().x];
		}

		sf::Uint8* GetMask(const sf::Texture* tex) {
			sf::Uint8* mask;
			std::map<const sf::Texture*, sf::Uint8*>::iterator pair = Bitmasks.find(tex);
			if (pair == Bitmasks.end())
			{
				sf::Image img = tex->copyToImage();
				mask = CreateMask(tex, img);
			}
			else
				mask = pair->second;

			return mask;
		}

		sf::Uint8* CreateMask(const sf::Texture* tex, const sf::Image& img) {
			sf::Uint8* mask = new sf::Uint8[tex->getSize().y * tex->getSize().x];

			for (unsigned int y = 0; y < tex->getSize().y; y++)
			{
				for (unsigned int x = 0; x < tex->getSize().x; x++)
					mask[x + y * tex->getSize().x] = img.getPixel(x, y).a;
			}

			Bitmasks.insert(std::pair<const sf::Texture*, sf::Uint8*>(tex, mask));

			return mask;
		}
	private:
		std::map<const sf::Texture*, sf::Uint8*> Bitmasks;
	};

	BitmaskManager Bitmasks;

	bool singlePixelTest(const sf::Sprite& Object1, sf::Vector2f& mousePosition, sf::Uint8 AlphaLimit) {
		if (Object1.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
			sf::IntRect O1SubRect = Object1.getTextureRect();
			sf::Uint8* mask1 = Bitmasks.GetMask(Object1.getTexture());

			sf::Vector2f o1v = Object1.getInverseTransform().transformPoint(mousePosition.x, mousePosition.y);
			// Make sure pixels fall within the sprite's subrect
			if (o1v.x > 0 && o1v.y > 0 && o1v.x < O1SubRect.width && o1v.y < O1SubRect.height) {
				if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int)(o1v.x) + O1SubRect.left, (int)(o1v.y) + O1SubRect.top) > AlphaLimit) {
					return true;
				}
			}
		}
		return false;
	}

	bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit) {
		sf::FloatRect Intersection;
		if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), Intersection)) {
			sf::IntRect O1SubRect = Object1.getTextureRect();
			sf::IntRect O2SubRect = Object2.getTextureRect();

			sf::Uint8* mask1 = Bitmasks.GetMask(Object1.getTexture());
			sf::Uint8* mask2 = Bitmasks.GetMask(Object2.getTexture());

			// Loop through our pixels
			for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++) {
				for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++) {

					sf::Vector2f o1v = Object1.getInverseTransform().transformPoint(i, j);
					sf::Vector2f o2v = Object2.getInverseTransform().transformPoint(i, j);

					// Make sure pixels fall within the sprite's subrect
					if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
						o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
						o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

						if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int)(o1v.x) + O1SubRect.left, (int)(o1v.y) + O1SubRect.top) > AlphaLimit &&
							Bitmasks.GetPixel(mask2, Object2.getTexture(), (int)(o2v.x) + O2SubRect.left, (int)(o2v.y) + O2SubRect.top) > AlphaLimit)
							return true;

					}
				}
			}
		}
		return false;
	}

	bool CreateTextureAndBitmask(sf::Texture& LoadInto, const std::string& Filename)
	{
		sf::Image img;
		if (!img.loadFromFile(Filename))
			return false;
		if (!LoadInto.loadFromImage(img))
			return false;

		Bitmasks.CreateMask(&LoadInto, img);
		return true;
	}

	sf::Vector2f GetSpriteCenter(const sf::Sprite& Object)
	{
		sf::FloatRect AABB = Object.getGlobalBounds();
		return sf::Vector2f(AABB.left + AABB.width / 2.f, AABB.top + AABB.height / 2.f);
	}

	sf::Vector2f GetSpriteSize(const sf::Sprite& Object)
	{
		sf::IntRect OriginalSize = Object.getTextureRect();
		sf::Vector2f Scale = Object.getScale();
		return sf::Vector2f(OriginalSize.width * Scale.x, OriginalSize.height * Scale.y);
	}

	bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
		sf::Vector2f Obj1Size = GetSpriteSize(Object1);
		sf::Vector2f Obj2Size = GetSpriteSize(Object2);
		float Radius1 = (Obj1Size.x + Obj1Size.y) / 4;
		float Radius2 = (Obj2Size.x + Obj2Size.y) / 4;

		sf::Vector2f Distance = GetSpriteCenter(Object1) - GetSpriteCenter(Object2);

		return (Distance.x * Distance.x + Distance.y * Distance.y <= (Radius1 + Radius2) * (Radius1 + Radius2));
	}

	class OrientedBoundingBox // Used in the BoundingBoxTest
	{
	public:
		sf::Vector2f Points[4];
		OrientedBoundingBox();
		OrientedBoundingBox(sf::RectangleShape* Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
		{
			sf::Transform trans = Object->getTransform();
			sf::IntRect local = Object->getTextureRect();
			Points[0] = trans.transformPoint(0.f, 0.f);
			Points[1] = trans.transformPoint(Object->getSize().x, 0.f);
			Points[2] = trans.transformPoint(Object->getSize().x, Object->getSize().y);
			Points[3] = trans.transformPoint(0.f, Object->getSize().y);
			
		}

		OrientedBoundingBox(sf::Sprite* Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
		{
			sf::Transform trans = Object->getTransform();
			sf::IntRect local = Object->getTextureRect();
			Points[0] = trans.transformPoint(0.f, 0.f);
			Points[1] = trans.transformPoint(local.width, 0.f);
			Points[2] = trans.transformPoint(local.width, local.height);
			Points[3] = trans.transformPoint(0.f, local.height);

			/*for (int i = 0; i < 4; i++) {
				printf("%f %f\n", Points[i].x, Points[i].y);
			}
			printf("\n");*/
		}
		
		void ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
		{
			Min = (Points[0].x * Axis.x + Points[0].y * Axis.y);
			Max = Min;
			for (int j = 1; j < 4; j++)
			{
				float Projection = (Points[j].x * Axis.x + Points[j].y * Axis.y);

				if (Projection < Min)
					Min = Projection;
				if (Projection > Max)
					Max = Projection;
			}
		}
	};

	bool BoundingBoxTest(sf::RectangleShape* Object1, sf::RectangleShape* Object2) {

		OrientedBoundingBox OBB1(Object1);
		OrientedBoundingBox OBB2(Object2);

		// Create the four distinct axes that are perpendicular to the edges of the two rectangles
		sf::Vector2f Axes[4] = {
			sf::Vector2f(OBB1.Points[1].x - OBB1.Points[0].x,
			OBB1.Points[1].y - OBB1.Points[0].y),
			sf::Vector2f(OBB1.Points[1].x - OBB1.Points[2].x,
			OBB1.Points[1].y - OBB1.Points[2].y),
			sf::Vector2f(OBB2.Points[0].x - OBB2.Points[3].x,
			OBB2.Points[0].y - OBB2.Points[3].y),
			sf::Vector2f(OBB2.Points[0].x - OBB2.Points[1].x,
			OBB2.Points[0].y - OBB2.Points[1].y)
		};

		for (int i = 0; i < 4; i++) // For each axis...
		{
			float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

			// ... project the points of both OBBs onto the axis ...
			OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
			OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

			// ... and check whether the outermost projected points of both OBBs overlap.
			// If this is not the case, the Separating Axis Theorem states that there can be no collision between the rectangles
			if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
				return false;
		}
		return true;
	}

	bool BoundingBoxTest(sf::RectangleShape* Object1, sf::Sprite* Object2) {

		OrientedBoundingBox OBB1(Object1);
		OrientedBoundingBox OBB2(Object2);

		// Create the four distinct axes that are perpendicular to the edges of the two rectangles
		sf::Vector2f Axes[4] = {
			sf::Vector2f(OBB1.Points[1].x - OBB1.Points[0].x,
			OBB1.Points[1].y - OBB1.Points[0].y),
			sf::Vector2f(OBB1.Points[1].x - OBB1.Points[2].x,
			OBB1.Points[1].y - OBB1.Points[2].y),
			sf::Vector2f(OBB2.Points[0].x - OBB2.Points[3].x,
			OBB2.Points[0].y - OBB2.Points[3].y),
			sf::Vector2f(OBB2.Points[0].x - OBB2.Points[1].x,
			OBB2.Points[0].y - OBB2.Points[1].y)
		};

		for (int i = 0; i < 4; i++) // For each axis...
		{
			float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

			// ... project the points of both OBBs onto the axis ...
			OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
			OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

			// ... and check whether the outermost projected points of both OBBs overlap.
			// If this is not the case, the Separating Axis Theorem states that there can be no collision between the rectangles
			if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
				return false;
		}
		return true;
	}
	bool BoundingBoxTest(sf::CircleShape* Object1, sf::Sprite* Object2)
	{
		OrientedBoundingBox OBB2(Object2);
		sf::Vector2f line[4][2] = {
			{OBB2.Points[0], OBB2.Points[1]},
			{OBB2.Points[1], OBB2.Points[2]},
			{OBB2.Points[2], OBB2.Points[3]},
			{OBB2.Points[3], OBB2.Points[0]},
		};
		float temp[4][3];
		for (int i = 0; i < 4; i++) {
			temp[i][0] = line[i][1].y - line[i][0].y;
			temp[i][1] = line[i][0].x - line[i][1].x;
			temp[i][2] = -(temp[i][0] * line[i][0].x + temp[i][1] * line[i][0].y);
		}
		std::vector<sf::Vector2f> P = { OBB2.Points[0] , OBB2.Points[1] ,OBB2.Points[2] ,OBB2.Points[3] };
		if (insidePolygon(P, 4, Object1->getPosition())) return true;
		for (int i = 0; i < 4; i++) {
			std::vector<float> P = { temp[i][0], temp[i][1], temp[i][2] };
			if (lineintercircle(Object1, OBB2.Points[i], i == 3 ? OBB2.Points[0] : OBB2.Points[i + 1], P))
			{
				return true;
			}

		}
		return false;
	}
	bool BoundingBoxTest(sf::CircleShape* Object1, sf::RectangleShape* Object2)
	{
		OrientedBoundingBox OBB2(Object2);
		sf::Vector2f line[4][2] = {
			{OBB2.Points[0], OBB2.Points[1]},
			{OBB2.Points[1], OBB2.Points[2]},
			{OBB2.Points[2], OBB2.Points[3]},
			{OBB2.Points[3], OBB2.Points[0]},
		};
		float temp[4][3];
		for (int i = 0; i < 4; i++) {
			temp[i][0] = line[i][1].y - line[i][0].y;
			temp[i][1] = line[i][0].x - line[i][1].x;
			temp[i][2] = -(temp[i][0] * line[i][0].x + temp[i][1] * line[i][0].y);
		}
		std::vector<sf::Vector2f> P = { OBB2.Points[0] , OBB2.Points[1] ,OBB2.Points[2] ,OBB2.Points[3] };
		if (insidePolygon(P, 4, Object1->getPosition())) return true;
		for (int i = 0; i < 4; i++) {
			std::vector<float> P = { temp[i][0], temp[i][1], temp[i][2] };
			
			if (lineintercircle(Object1, OBB2.Points[i], i == 3? OBB2.Points[0] : OBB2.Points[i+1] ,P))
			{
				
				return true;
			}

		}
		return false;
	}
	bool WillBoundingBoxTest(sf::RectangleShape* Object1, sf::RectangleShape* Object2, float movex, float movey) {
		temp1 = *Object1;
		temp2 = *Object2;
		//float dist1 = sqrt((temp1.getPosition().x - temp2.getPosition().x) * (temp1.getPosition().x - temp2.getPosition().x) - (temp1.getPosition().y - temp2.getPosition().y) * (temp1.getPosition().y - temp2.getPosition().y));
		temp1.move(movex, movey);
		//float dist2 = sqrt((temp1.getPosition().x - temp2.getPosition().x) * (temp1.getPosition().x - temp2.getPosition().x) - (temp1.getPosition().y - temp2.getPosition().y) * (temp1.getPosition().y - temp2.getPosition().y));
		//if (dist2 > dist1) return false;
		OrientedBoundingBox OBB1(&temp1);
		OrientedBoundingBox OBB2(&temp2);

		// Create the four distinct axes that are perpendicular to the edges of the two rectangles
		sf::Vector2f Axes[4] = {
			sf::Vector2f(OBB1.Points[1].x - OBB1.Points[0].x,
			OBB1.Points[1].y - OBB1.Points[0].y),
			sf::Vector2f(OBB1.Points[1].x - OBB1.Points[2].x,
			OBB1.Points[1].y - OBB1.Points[2].y),
			sf::Vector2f(OBB2.Points[0].x - OBB2.Points[3].x,
			OBB2.Points[0].y - OBB2.Points[3].y),
			sf::Vector2f(OBB2.Points[0].x - OBB2.Points[1].x,
			OBB2.Points[0].y - OBB2.Points[1].y)
		};

		for (int i = 0; i < 4; i++) // For each axis...
		{
			float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

			// ... project the points of both OBBs onto the axis ...
			OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
			OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

			// ... and check whether the outermost projected points of both OBBs overlap.
			// If this is not the case, the Separating Axis Theorem states that there can be no collision between the rectangles
			if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
				return false;
		}
		return true;
	}
	float dist(sf::Vector2f v1, sf::Vector2f v2)
	{
		return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
	}
	float degree(sf::Vector2f p1, sf::Vector2f p2)
	{
		if (p1.x == p2.x) return (p1.y >= p2.y ? 1 : -1 ) * 90.f;
		if (p1.y == p2.y) return (p1.x >= p2.x ? 1 : 0) * 180.f;
		if (p1.x < p2.x)  return 1.f * atan((p1.y - p2.y) / (p2.x - p1.x)) * 57.2957795;
		if (p1.x > p2.x) return 180.f - atan((p1.y - p2.y) / (p1.x - p2.x)) * 57.2957795;
 	}
}