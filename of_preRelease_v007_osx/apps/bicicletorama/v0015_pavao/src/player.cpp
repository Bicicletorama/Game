
#include "player.h"



void player::setup(int _playerID, b2World * b2dworld)
{
    BIKE_HEIGHT = 30;
    BIKE_WIDTH = 5;
    WHEEL_HEIGHT = 10;
    WHEEL_WIDTH = 2.5;
    
    BIKE_DENSITY = 1;
    BIKE_BOUNCE = 0.5;
    BIKE_FRICTION = 0.1;
    
    HORSEPOWERS = 70;
    MAX_STEER_ANGLE = PI/2.5;
    FLOOR_FRICTION = 0.7;
    
    MAX_IDLE_TIME = 10 * 1000;
    
    playerID = _playerID;
    
    switch(playerID)
    {
        case 0:
            color.setHex(0x22f960);
            break;
        case 1:
            color.setHex(0xfff220);
            break;
        case 2:
            color.setHex(0xf9222b);
            break;
        case 3:
            color.setHex(0x22d3f9);
            break;
        default:
            color.setHex(0xffffff);
            break;
    }
    
    engineSpeed = 0;
    steeringAngle = 0;
    
    idle = true;
    lastImpulseTime = ofGetElapsedTimeMillis();
    
    //sprite bike
    spriteBike.addFile("images/player/"+ofToString(playerID+1)+"/bike/1.png");
    spriteBike.addFile("images/player/"+ofToString(playerID+1)+"/bike/2.png");
    spriteBike.addFile("images/player/"+ofToString(playerID+1)+"/bike/3.png");
    spriteBike.addFile("images/player/"+ofToString(playerID+1)+"/bike/4.png");
    spriteBike.setAnchorPercent(0.5, 0.5); 
    
    //sprite wheel
    spriteFront.addFile("images/player/"+ofToString(playerID+1)+"/front/1.png");
    spriteFront.addFile("images/player/"+ofToString(playerID+1)+"/front/2.png");
    spriteFront.addFile("images/player/"+ofToString(playerID+1)+"/front/3.png");
    spriteFront.addFile("images/player/"+ofToString(playerID+1)+"/front/4.png");
    spriteFront.addFile("images/player/"+ofToString(playerID+1)+"/front/5.png");
    spriteFront.addFile("images/player/"+ofToString(playerID+1)+"/front/6.png");
    spriteFront.addFile("images/player/"+ofToString(playerID+1)+"/front/7.png");
    spriteFront.addFile("images/player/"+ofToString(playerID+1)+"/front/8.png");
    spriteFront.addFile("images/player/"+ofToString(playerID+1)+"/front/9.png");
    spriteFront.setAnchorPercent(0.5, 0.5);
    
    //box2d
    bike.setPhysics(BIKE_DENSITY, BIKE_BOUNCE, BIKE_FRICTION);
    bike.setup(b2dworld, 0, 0, BIKE_WIDTH, BIKE_HEIGHT);
    
    frontWheel.setPhysics(BIKE_DENSITY, BIKE_BOUNCE, BIKE_FRICTION);
    frontWheel.setup(b2dworld, 0, -BIKE_HEIGHT, WHEEL_WIDTH, WHEEL_HEIGHT);
    
    rearWheel.setPhysics(BIKE_DENSITY, BIKE_BOUNCE, BIKE_FRICTION);
    rearWheel.setup(b2dworld, 0, +BIKE_HEIGHT, WHEEL_WIDTH, WHEEL_HEIGHT);    
    
    b2RevoluteJointDef* frontJointDef = new b2RevoluteJointDef();
    frontJointDef->Initialize(bike.body, frontWheel.body, frontWheel.body->GetWorldCenter());
    frontJointDef->enableMotor = true;
    frontJointDef->maxMotorTorque = 100;
    frontJoint = (b2RevoluteJoint*)b2dworld->CreateJoint(frontJointDef);
    
    b2PrismaticJointDef* rearJointDef = new b2PrismaticJointDef();
    rearJointDef->Initialize(bike.body, rearWheel.body, rearWheel.body->GetWorldCenter(), b2Vec2(1,0));
    rearJointDef->enableLimit = true;
    rearJointDef->lowerTranslation = 0;
    rearJointDef->upperTranslation = 0;
    b2dworld->CreateJoint(rearJointDef);
}

void player::goToStartPosition() 
{   
    float x = 250;
    float y = 120 + (playerID*50);
    float angle = PI/2.0;
    
    bike.body->SetTransform(b2Vec2(b2dNum(x), b2dNum(y)), angle);
    frontWheel.body->SetTransform(b2Vec2(b2dNum(x+BIKE_HEIGHT), b2dNum(y)), angle);
    rearWheel.body->SetTransform(b2Vec2(b2dNum(x-BIKE_HEIGHT), b2dNum(y)), angle);
    
    bike.body->SetActive(false);
    frontWheel.body->SetActive(false);
    rearWheel.body->SetActive(false);
    
    steeringAngle = 0;
    
    idle = true;
    
    lastImpulseTime = ofGetElapsedTimeMillis();
}

void player::wakeUp()
{
    bike.body->SetActive(true);
    frontWheel.body->SetActive(true);
    rearWheel.body->SetActive(true);
    
    engineSpeed = 0;
    steeringAngle = 0;
    
    idle = false;
}

void player::sleep()
{
    goToStartPosition();
}

void player::setDirectionIncrement(float increment) 
{
    increment *= 0.25;
    setDirection(steeringAngle + increment);
}

void player::setDirection(float value) 
{
    if (value > 1) value = 1;
    if (value < -1) value = -1;
    
    float angle = bike.body->GetAngle();
    angle += value * MAX_STEER_ANGLE;
    
    //cout << "ANGLE " << angle << endl;
    
    if (angle > PI) {
        angle = -PI + (angle - PI);
    }
    if (angle < -PI) {
        angle = PI + (angle + PI);
    }
    
    frontWheel.body->SetTransform(frontWheel.body->GetPosition(), angle);
    
    steeringAngle = value;
}

void player::applyImpulse() 
{
    if (idle) {
        wakeUp();
    }
    
    bike.body->SetAwake(true);
    engineSpeed = -HORSEPOWERS;
    
    lastImpulseTime = ofGetElapsedTimeMillis();
    
    spriteBike.nextFrame();
}

void player::update(float direction, float total_impulses) 
{
    if (USE_ARDUINO)
    {
        setDirection(direction);
     
        for (int i = 0; i < total_impulses; i++) {
            applyImpulse();
        }
    }
    
    killOrthogonalVelocity(frontWheel.body);
    killOrthogonalVelocity(rearWheel.body);
    
    //Driving
    b2Vec2 frontWheelDirection = frontWheel.body->GetTransform().R.col2;
    frontWheelDirection *= engineSpeed;
    frontWheel.body->ApplyForce(frontWheelDirection, frontWheel.body->GetPosition());
    
    //decelerate (friction with floor)
    b2Vec2 rv = rearWheel.body->GetLinearVelocity();
    rv *= FLOOR_FRICTION;
	rearWheel.body->SetLinearVelocity(rv);
    
    //reset engine speed until next applyImpulse()
    engineSpeed = 0;
    
    //check if is time to be idle
    if (ofGetElapsedTimeMillis() - lastImpulseTime > MAX_IDLE_TIME) {
        sleep();
    }
    
    //position
    oldX = x;
    oldY = y;
    x = (2*rearWheel.getPosition().x + bike.getPosition().x)/3;
    y = (2*rearWheel.getPosition().y + bike.getPosition().y)/3;
}

void player::killOrthogonalVelocity(b2Body* targetBody)
{
	b2Vec2 localPoint = b2Vec2(0,0);
	b2Vec2 velocity = targetBody->GetLinearVelocityFromLocalPoint(localPoint);
    
    b2Vec2 sidewaysAxis = targetBody->GetTransform().R.col2;
	sidewaysAxis *= b2Dot(velocity,sidewaysAxis);
    
	targetBody->SetLinearVelocity(sidewaysAxis);
}

void player::draw() 
{
    ofPushStyle();
    
    if (idle) {
        ofSetColor(255, 255, 255, 60);
    } else {
        //ofSetColor(color);
    }
    
    //wheel
    spriteFront.setCurrentFrame( ofMap(steeringAngle, -1, 1, 0, 8) );
    spriteFront.setRotation(bike.getRotation());
    spriteFront.setPosition(frontWheel.getPosition());
    spriteFront.draw();
    
    //bike
    spriteBike.setRotation(bike.getRotation());
    spriteBike.setPosition(bike.getPosition());
    spriteBike.draw();
    
    ofPopStyle();
}

float player::getVelocity()
{
    float vel = bike.getVelocity().squareLength();
    return (vel > 0.01) ? vel : 0;
}


