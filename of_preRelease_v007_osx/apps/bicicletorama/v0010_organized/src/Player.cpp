
#include "player.h"


Player::Player()
{
    
}

void Player::setup(int _playerID, b2World * b2dworld)
{
    playerID = _playerID;
    
    switch(playerID){
        case 0:
            color.set(255, 0, 0);
            break;
        case 1:
            color.set(0, 255, 0);
            break;
        case 2:
            color.set(0, 100, 100);
            break;
        case 3:
            color.set(255, 255, 0);
            break;
        default:
            color.set(255, 255, 255);
            break;
    }
    
    
    engineSpeed = 0;
    steeringAngle = 0;
    
    idle = true;
    idleTime = 0;
    
    locked = true;
    
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

void Player::goToStartPosition(bool lockTime) 
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
    
    idle = true;
    
    idleTime = 0;
    
    locked = lockTime;
}

void Player::wakeUp()
{
    bike.body->SetActive(true);
    frontWheel.body->SetActive(true);
    rearWheel.body->SetActive(true);
    
    engineSpeed = 0;
    steeringAngle = 0;
    
    idle = false;
}

void Player::sleep()
{
    goToStartPosition(false);
}

void Player::setDirectionIncrement(float increment) 
{
    increment *= 0.25;
    setDirection(steeringAngle + increment);
}

void Player::setDirection(float value) 
{
    if (value > 1) value = 1;
    if (value < -1) value = -1;
    
    float angle = bike.body->GetAngle();
    angle += value * MAX_STEER_ANGLE;
    
    if (angle > PI) {
        angle = -PI + (angle - PI);
    }
    if (angle < -PI) {
        angle = PI + (angle + PI);
    }
    
    frontWheel.body->SetTransform(frontWheel.body->GetPosition(), angle);
    
    steeringAngle = value;
}

void Player::applyImpulse() 
{
    if (!locked)
    {
        if (idle) {
            wakeUp();
        }
        
        bike.body->SetAwake(true);
        engineSpeed = -HORSEPOWERS;
        
        idleTime = 0;
        
        sprite.nextFrame();
    }
}

void Player::killOrthogonalVelocity(b2Body* targetBody)
{
	b2Vec2 localPoint = b2Vec2(0,0);
	b2Vec2 velocity = targetBody->GetLinearVelocityFromLocalPoint(localPoint);
    
    b2Vec2 sidewaysAxis = targetBody->GetTransform().R.col2;
	sidewaysAxis *= b2Dot(velocity,sidewaysAxis);
    
	targetBody->SetLinearVelocity(sidewaysAxis);
}

void Player::update(int potenciometro, int reed, bool useArduino) 
{
    if (useArduino) {
        //potenciometro
        int middle = 490;
        int range = 300;
        setDirection( ofMap(potenciometro, middle-range, middle+range, -1, 1) );
        
        //reed
        if (reed != lastReed) {
            lastReed = reed;
            if (reed == 1) {
                applyImpulse();
            }
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
    idleTime++;
    if (idleTime > MAX_IDLE_TIME) {
        sleep();
    }
    
    //sprite
    sprite.update();
    
    //position
    oldX = x;
    oldY = y;
    x = bike.getPosition().x;
    y = bike.getPosition().y;
}

void Player::draw() 
{
    if (idle) {
        ofSetColor(color, 100);
    } else {
        ofSetColor(color);
    }
    
    ofPushMatrix();
        ofTranslate(frontWheel.getPosition().x, frontWheel.getPosition().y);
        ofRotate(frontWheel.getRotation());
        imageFrontWheel.draw(-imageFrontWheel.getWidth()/2.0, -imageFrontWheel.getHeight()/2.0);
    ofPopMatrix();
    
    sprite.setRotation(bike.getRotation());
    sprite.setPosition(bike.getPosition());
    sprite.draw();
    
    /*
    //debug box2d
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


