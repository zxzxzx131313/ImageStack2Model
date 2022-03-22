#include "ofApp.h"


void ofApp::dilate( ofImage & imgSrc, ofImage & imgDest, bool dilate_white){
    
    // assumptions!
    // img1 / img2 same w/h
    // both grayscale / binary images
    
    for (int i = 0; i < imgSrc.getWidth(); i++){
        for (int j = 0; j < imgSrc.getHeight(); j++){
            
            // neighbors
            // edges
            
            int i_m_1 = ofClamp(i-1, 0, imgSrc.getWidth()-1);
            int i_p_1 = ofClamp(i+1, 0, imgSrc.getWidth()-1);
            int j_m_1 = ofClamp(j-1, 0, imgSrc.getHeight()-1);
            int j_p_1 = ofClamp(j+1, 0, imgSrc.getHeight()-1);
            
            // neighbor values
            
            ofColor n_ = imgSrc.getColor(i,j_p_1);
            ofColor ne = imgSrc.getColor(i_p_1,j_p_1);
            ofColor e_ = imgSrc.getColor(i_p_1,j);
            ofColor se = imgSrc.getColor(i_p_1,j_m_1);
            ofColor s_ = imgSrc.getColor(i,j_m_1);
            ofColor sw = imgSrc.getColor(i_m_1,j_m_1);
            ofColor w_ = imgSrc.getColor(i_m_1,j);
            ofColor nw = imgSrc.getColor(i_m_1,j_p_1);
            if (dilate_white) {
                if (  n_.getBrightness() > 127 ||
                      ne.getBrightness() > 127 ||
                    e_.getBrightness() > 127 ||
                    se.getBrightness() > 127 ||
                    s_.getBrightness() > 127 ||
                    sw.getBrightness() > 127 ||
                    w_.getBrightness() > 127 ||
                    nw.getBrightness() > 127 ){
                    imgDest.setColor(i,j, ofColor(255));
                } else {
                    imgDest.setColor(i,j, ofColor(0));
                }
            } else {
                if (  n_.getBrightness() < 127 ||
                      ne.getBrightness() < 127 ||
                    e_.getBrightness() < 127 ||
                    se.getBrightness() < 127 ||
                    s_.getBrightness() < 127 ||
                    sw.getBrightness() < 127 ||
                    w_.getBrightness() < 127 ||
                    nw.getBrightness() < 127 ){
                    imgDest.setColor(i,j, ofColor(0));
                } else {
                    imgDest.setColor(i,j, ofColor(255));
                }
            }
        }
    }
    
    imgDest.update();
    
    
}
//--------------------------------------------------------------
void ofApp::setup(){

    
    ofDirectory dir;
    dir.listDir("walk2_video_generated");
    for (int i = 0; i < dir.size(); i++){
        ofImage img;
        images.push_back(img);
    }
    for (int i = 0; i < dir.size(); i++){
        string delimiter = ".jpg";
        string file_name = dir.getFiles().at(i).getFileName();

        int file_id = stoi(file_name.substr(29, file_name.find(delimiter)));
        
        images[file_id].load(dir.getPath(i));

        
        images[file_id].setImageType(OF_IMAGE_GRAYSCALE);
        
        
        ofImage postImg;
        postImg.allocate(images[file_id].getWidth(), images[file_id].getHeight(), OF_IMAGE_GRAYSCALE);

        post.push_back(postImg);
        
    }

    for (int i = images.size()-1; i >= 0 ; i--){
        int dark = 0;
        int light = 0;

        for (int j = 0; j < 1024; j++){
            for (int k = 0; k < 1024; k++){
                float brightness = images[i].getColor(j,k).getBrightness();

                int color = 255;
                if (brightness > 149) {
                    color = 0;
                    light ++;
                } else {
                    dark ++;
                }
                
                if (i < images.size()-1) {
                    if (images[i+1].getColor(j,k) == 0) {
                        color = 0;
                    }
                }
                
                images[i].setColor(j,k, ofColor(color));
            }
        }

//        if (dark > light) {
//            cout << "i: " << i << " dark: " << dark << " light: " << light << endl;
//            for (int j = 0; j < 1024; j++){
//                for (int k = 0; k < 1024; k++){
//                    ofColor c = images[i].getColor(j, k).invert();
//                    images[i].setColor(j, k, c);
//                }
//            }
//        }
        images[i].update();

        images[i].save("out/"+to_string(i)+".jpg");
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

//    images[ ofMap(mouseX, 0, ofGetWidth(),
//                  0, images.size()-1, true)].draw(0,0);
    images[ ofMap(mouseX, 0, ofGetWidth(),
                  0, images.size()-1, true)].draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
