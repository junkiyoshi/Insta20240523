#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("openFrameworks");
	ofSetFrameRate(25);

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int x = -270; x <= 270; x += 60) {

		for (int y = -270; y <= 270; y += 60) {

			for (int size = 15; size <= 35; size += 20) {

				ofPushMatrix();
				ofTranslate(x, y);

				auto distance = glm::length(glm::vec2(x, y));

				auto x_value = ofNoise(noise_seed.x, size * 0.005 + distance * 0.001 - ofGetFrameNum() * 0.015);
				auto y_value = ofNoise(noise_seed.y, size * 0.005 + distance * 0.001 - ofGetFrameNum() * 0.015);
				auto z_value = ofNoise(noise_seed.z, size * 0.005 + distance * 0.001 - ofGetFrameNum() * 0.015);

				auto x_deg = x_value < 0.35 ? ofMap(x_value, 0, 0.35, -360, 0) : x_value > 0.75 ? ofMap(x_value, 0.75, 1, 0, 360) : 0;
				auto y_deg = y_value < 0.35 ? ofMap(y_value, 0, 0.35, -360, 0) : y_value > 0.75 ? ofMap(y_value, 0.75, 1, 0, 360) : 0;
				auto z_deg = z_value < 0.35 ? ofMap(z_value, 0, 0.35, -360, 0) : z_value > 0.75 ? ofMap(z_value, 0.75, 1, 0, 360) : 0;

				ofRotateZ(z_deg);
				ofRotateY(y_deg);
				ofRotateX(x_deg);

				ofNoFill();
				ofDrawBox(size);

				ofPopMatrix();
			}
		}
	}

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/

}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}