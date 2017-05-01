#include "Animation.h"
#include<iostream>

Animation::Animation(const Vector2 & position, const float & width, const float & height) : Renderable(position, rotation, width, height) {

}

Animation::~Animation() {
	for(std::vector<Image*>::iterator i = frames.begin(); i != frames.end(); ++i) 
		delete * i;
	frames.clear();
}

void Animation::Draw(const Vector2 & origin, const float & rotation) {
	if(GetNoOfFrames() > 0) {
		frames[currentFrame]->Draw(origin, rotation);
	}
}

void Animation::AddFrame(Image * image) {
	image->SetPosition(center);
	frames.push_back(image);
}

float Animation::GetSwitchRate() {
	return frameSwitchRate;
}

void Animation::SetSwitchRate(const float & rate) {
	frameSwitchRate = rate;
}

void Animation::Update(const float & deltaTime) {
	switchTimer += deltaTime;
	if(switchTimer >= frameSwitchRate) {
		MoveToNextFrame();
	}
}

int Animation::GetNoOfFrames() {
	return frames.size();
}

RenderableType Animation::GetType() {
	return ANIMATION;
}

void Animation::MoveToNextFrame() {
	currentFrame++;
	if(currentFrame >= GetNoOfFrames()) 
		currentFrame = 0;
	switchTimer -= frameSwitchRate;
}