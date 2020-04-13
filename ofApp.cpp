#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto R = 200;
	auto r = 35;
	auto v_span = 8;
	auto u_span = 10;
	auto v = 0;

	this->cam.begin();
	ofRotateX(300);

	ofColor color;
	for (auto deg = 0; deg < 360; deg += v_span) {

		color.setHsb(ofMap(deg, 0, 360, 0, 255), 255, 255);

		ofMesh face, frame;
		frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

		for (auto u = 0; u < 360; u += u_span) {

			vector<glm::vec3> vertices;
			vertices.push_back(this->make_point(R, r, u, v - v_span * 0.5));
			vertices.push_back(this->make_point(R, r, u + u_span, v - v_span * 0.5));
			vertices.push_back(this->make_point(R, r, u + u_span, v + v_span * 0.5));
			vertices.push_back(this->make_point(R, r, u, v + v_span * 0.5));

			int index = face.getNumVertices();
			face.addVertices(vertices);
			frame.addVertices(vertices);

			face.addIndex(index + 0); face.addIndex(index + 1); face.addIndex(index + 2);
			face.addIndex(index + 0); face.addIndex(index + 2); face.addIndex(index + 3);

			frame.addIndex(index + 0); frame.addIndex(index + 1);
			frame.addIndex(index + 1); frame.addIndex(index + 2);
			frame.addIndex(index + 2); frame.addIndex(index + 3);
			frame.addIndex(index + 3); frame.addIndex(index + 0);
		}

		ofPushMatrix();
		ofRotateZ(deg);

		int n = 360 / v_span;
		int frame_number = ofGetFrameNum() * 8;
		int param = frame_number % (360 * n) - (v_span * n * 0.5);
		if (deg * n >= param && deg * n < param + v_span * n){
		
			ofRotateY(frame_number);
		}
		else {

			param = (frame_number + 180 * n) % (360 * n) - (v_span * n * 0.5);
			if (deg * n >= param && deg * n < param + v_span * n) {

				ofRotateY(frame_number * -1);
			}
		}

		ofSetColor(239);
		face.drawFaces();

		ofSetColor(39);
		frame.drawWireframe();

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}