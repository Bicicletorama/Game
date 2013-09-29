#include "player.h"


player::player()
{
    
}

void player::setup(int _playerID, b2World * b2dworld)
{
    playerID = _playerID;
    
    engineSpeed = 0;
    steeringAngle = 0;
    
    idle = false;
    idleTime = 0;
    
    //sprite
    sprite.addFile("images/ciclista_sprite_1.png");
    sprite.addFile("images/ciclista_sprite_2.png");
    sprite.addFile("images/ciclista_sprite_3.png");
    sprite.addFile("images/ciclista_sprite_4.png");
    sprite.setAnchorPercent(0.5, 0.5); 
    
    imageFrontWheel.loadImage("images/ciclista_front_wheel.png");
    
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
    frontWheel.body->SetTransform(b2Vec2(b2dNum(x), b2dNum(y)), angle);
    rearWheel.body->SetTransform(b2Vec2(b2dNum(x), b2dNum(y)), angle);
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
    steeringAngle = value;
}

void player::applyImpulse() 
{
    if (idle) {
        wakeUp();
    }
    
    bike.body->SetAwake(true);
    engineSpeed = -HORSEPOWERS;
    
    idleTime = 0;
    
    sprite.nextFrame();
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
    
    bike.body->SetActive(false);
    frontWheel.body->SetActive(false);
    rearWheel.body->SetActive(false);
    
    idle = true;
}

void player::killOrthogonalVelocity(b2Body* targetBody)
{
	b2Vec2 localPoint = b2Vec2(0,0);
	b2Vec2 velocity = targetBody->GetLinearVelocityFromLocalPoint(localPoint);
    
    b2Vec2 sidewaysAxis = targetBody->GetTransform().R.col2;
	sidewaysAxis *= b2Dot(velocity,sidewaysAxis);
    
	targetBody->SetLinearVelocity(sidewaysAxis);
}

void player::update() 
{
    killOrthogonalVelocity(frontWheel.body);
    killOrthogonalVelocity(rearWheel.body);
    
    //Driving
    b2Vec2 frontWheelDirection = frontWheel.body->GetTransform().R.col2;
    frontWheelDirection *= engineSpeed;
    frontWheel.body->ApplyForce(frontWheelDirection, frontWheel.body->GetPosition());
    
    //Steering
    float mspeed;
    mspeed = (steeringAngle * MAX_STEER_ANGLE) - frontJoint->GetJointAngle();
    frontJoint->SetMotorSpeed(mspeed * STEER_SPEED);
    
    //decelerate (friction with floor)
    b2Vec2 rv = rearWheel.body->GetLinearVelocity();
    rv *= FLOOR_FRICTION;
	rearWheel.body->SetLinearVelocity(rv);
    
    //reset engine speed until next applyImpulse()
    engineSpeed = 0;
    
    //check if is time to be idle
    idleTime++;
    if (idleTime > MAX_IDLE_TIME) {
        sleep();
    }
    
    //sprite
    sprite.update();
}

void player::draw() 
{
    if (idle)
    {
        //ghost start pedal to play
        ofPushStyle();
            ofSetHexColor(0xff0000);
            ofCircle(bike.getPosition(), 10);
        ofPopStyle();
    }
    else
    {
        //biker
        ofPushMatrix();
            ofTranslate(frontWheel.getPosition().x, frontWheel.getPosition().y);
            ofRotate(frontWheel.getRotation());
            imageFrontWheel.draw(-imageFrontWheel.getWidth()/2.0, -imageFrontWheel.getHeight()/2.0);
        ofPopMatrix();
        
        sprite.setRotation(bike.getRotation());
        sprite.setPosition(bike.getPosition());
        sprite.draw();
    }
    
    /*
    //debug
    ofPushStyle();
        ofSetLineWidth(2);
        ofNoFill();
        ofSetHexColor(0xCCCCCC);
        frontWheel.draw();
        rearWheel.draw();
        ofSetHexColor(0xBF2545);
        bike.draw();
    ofPopStyle();
     */
}


