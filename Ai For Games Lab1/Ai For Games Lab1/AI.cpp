#include "AI.h"

AI::AI()
{
}

AI::~AI()
{
}

sf::Vector2f AI::getPosition()
{
	return sf::Vector2f();
}

void AI::setPosition()
{
	m_ai.setPosition(500, 500);
}
void AI::update(sf::VideoMode desktop, double dt, sf::Vector2f t_playerPos)
{
	switch (m_enemyBehaviour)
	{
	case EnemyBehaviour::SEEK_PLAYER:
		kinematicSeek(t_playerPos, dt);
		
		break;
	case EnemyBehaviour::WANDER_MAP:
		kinematicWander(dt);
		break;
	case EnemyBehaviour::FLEE:
		evade(t_playerPos, dt);
		break;
	case EnemyBehaviour::PURSUE:
		pursue(t_playerPos, dt);
		break;
	case EnemyBehaviour::ARRIVE:
		kinematicArrive(t_playerPos,dt);
		m_aiVals.velocity = m_arriveTargetVals.velocity;
		break;
	default:
		break;
	}
	
	m_text.setPosition(m_ai.getPosition() + m_textOffset);
	m_ai.setPosition(m_ai.getPosition() + sf::Vector2f(m_aiVals.velocity.x * dt / 1000,
		m_aiVals.velocity.y * dt / 1000));
	
	m_ai.setRotation(m_aiVals.rotation);
	float size = 57.5f;
	sf::Vector2f centre = sf::Vector2f(m_ai.getPosition().x + size, m_ai.getPosition().y - size);
	m_rayCast.setRayValues(centre, m_aiVals.direction, 1.0f);
	m_rayCast.hit(t_playerPos, 10);
	
	BoundryControl(desktop);
	
}
void AI::kinematicWander(float dt)
{
	sf::Vector2f target(m_ai.getPosition().x + m_wanderOffset.x, m_ai.getPosition().y + m_wanderOffset.y);
	getSteering(target);
	int random = rand() % 2 + 1;
	if (random == 2)
	{
		random = -1;
	}

	m_wanderOrientation += random * m_wanderRate;
	m_wanderTargetOrientation = m_wanderOrientation + m_aiVals.orientation;
	//To get the centre of the wander circle
	target = m_ai.getPosition() + m_wanderOffset * m_aiVals.orientation;
	target += sf::Vector2f(m_wanderRadius * m_wanderTargetOrientation , m_wanderRadius * m_wanderTargetOrientation);
	directionToFace(target);
	steering.linear = sf::Vector2f(m_maxAcelleration * m_aiVals.orientation, m_maxAcelleration * m_aiVals.orientation);

	/*m_aiVals.velocity = m_aiVals.velocity + sf::Vector2f(steering.linear.x * dt, steering.linear.y * dt);
	float vecLength = m_math.length(m_aiVals.velocity);
	if (vecLength > MaxSpeed)
	{
		m_aiVals.velocity = m_math.normalise(m_aiVals.velocity);
		m_aiVals.velocity = sf::Vector2f(m_aiVals.velocity.x * MaxSpeed, m_aiVals.velocity.y * MaxSpeed);
	}*/

	m_aiVals.velocity = sf::Vector2f(-sin(m_targetVals.orientation), cos(m_targetVals.orientation)) * MaxSpeed;
}

void AI::directionToFace(sf::Vector2f t_target)
{
	m_targetVals.position = t_target;
	m_direction = m_targetVals.position - m_ai.getPosition();
	float directionLength = m_math.length(m_direction);
	if (directionLength == 0) {}
	else
	{
		m_targetVals.orientation = atan2(-m_direction.x, m_direction.y);
		align();
	}
	if (m_aiVals.velocity == sf::Vector2f(0.0f,0.0f)) {}
	else
	{
		m_targetVals.orientation = atan2(m_aiVals.velocity.x, m_aiVals.velocity.y);
		align();
	}
	
}

void AI::align()
{
	getSteering(m_targetVals.position);
	m_targetVals.radius = 10.0f;
	m_aiVals.rotation = m_targetVals.orientation - m_aiVals.orientation;
	m_aiVals.rotation = mapToRange(m_aiVals.rotation);
	float rotationSize = abs(m_aiVals.rotation);
	if (rotationSize < m_targetVals.radius)
	{
		m_targetVals.rotation = 0;
	}
	else if (rotationSize > m_slowRadius)
	{
		m_targetVals.rotation = m_maxRotation;
	}
	else
	{ 
		m_targetVals.rotation = m_maxRotation * (rotationSize / m_slowRadius);
	}
	steering.angular = m_targetVals.rotation - m_aiVals.rotation;
	steering.angular = steering.angular / m_timeToTarget;
	float angularAbs = abs(steering.angular);
	if (angularAbs > m_maxAngular)
	{
		steering.angular = steering.angular / angularAbs;
		steering.angular = steering.angular * m_maxAngularAcc;
	}
	steering.linear = sf::Vector2f(0,0);


}

void AI::kinematicSeek(sf::Vector2f t_target ,double dt)
{

	getSteering(t_target);
	//std::cout << "Steeri9ngX: " << steering.linear.x << "  Steeri9ngY: " << steering.linear.y << std::endl;
	m_aiVals.velocity = m_aiVals.velocity + sf::Vector2f(steering.linear.x * dt, steering.linear.y * dt);
	m_aiVals.rotation = m_aiVals.rotation + steering.angular * dt;
	float vecLength = m_math.length(m_aiVals.velocity);
	if (vecLength > MaxSpeed)
	{
		m_aiVals.velocity = m_math.normalise(m_aiVals.velocity);
		m_aiVals.velocity = sf::Vector2f(m_aiVals.velocity.x * MaxSpeed, m_aiVals.velocity.y * MaxSpeed);
	}
	if (m_aiVals.rotation > m_maxRotation)
	{
		m_aiVals.rotation = m_maxRotation;
	}
	else if (-m_aiVals.rotation > m_maxRotation)
	{
		m_aiVals.rotation = -m_maxRotation;
	}
	m_aiVals.position = m_aiVals.position + sf::Vector2f(m_aiVals.velocity.x * dt, m_aiVals.velocity.y * dt);
	m_aiVals.orientation = m_aiVals.orientation + m_aiVals.rotation * dt;

	//old code for the kinematic seek that has been replaced by the new code for the seek with steering
	/*m_aiVals.velocity = m_playerPos - m_ai.getPosition();
	m_aiVals.velocity = m_math.normalise(m_aiVals.velocity);
	m_aiVals.velocity = m_aiVals.velocity * MaxSpeed;
	m_aiVals.orientation = getNewOrientation(m_aiVals.orientation, m_aiVals.velocity);*/
}

void AI::kinematicArrive(sf::Vector2f m_playerPos, float dt)
{
	getSteering(m_playerPos);
	m_arrivalRadius = m_player.getCircleRadius();
	m_aiVals.direction = m_playerPos - m_ai.getPosition();
	m_aiVals.distance = m_math.length(m_aiVals.direction);
	if (m_aiVals.distance < m_arrivalRadius)
	{
		m_targetSpeed = 0.0f;
	}
	else if (m_aiVals.distance > m_slowRadius)
	{
		m_targetSpeed = MaxSpeed * (m_aiVals.distance / m_slowRadius);
	}
	m_arriveTargetVals.velocity = m_aiVals.direction;
	m_arriveTargetVals.velocity = m_math.normalise(m_arriveTargetVals.velocity);
	m_arriveTargetVals.velocity = m_arriveTargetVals.velocity * m_targetSpeed / dt;

	m_timeToTarget =0.1f;
	steering.linear = m_arriveTargetVals.velocity - m_aiVals.velocity;
	steering.linear = steering.linear / m_timeToTarget;
	float steerLength = m_math.length(steering.linear);
	if (steerLength > m_maxAcelleration)
	{
		steering.linear = m_math.normalise(steering.linear);
		steering.linear = steering.linear * m_maxAcelleration;
	}
	steering.angular = 0;

}


void AI::kinematicFlee(sf::Vector2f t_target, double dt)
{
	getSteering(t_target);
	MaxSpeed = 1.5f;
	m_aiVals.velocity = m_aiVals.velocity + sf::Vector2f(steering.linear.x * dt, steering.linear.y * dt);
	m_aiVals.rotation = m_aiVals.rotation + steering.angular * dt;
	float vecLength = m_math.length(m_aiVals.velocity);
	if (vecLength > MaxSpeed)
	{
		m_aiVals.velocity = m_math.normalise(m_aiVals.velocity);
		m_aiVals.velocity = sf::Vector2f(m_aiVals.velocity.x * MaxSpeed, m_aiVals.velocity.y * MaxSpeed);
	}
	if (m_aiVals.rotation > m_maxRotation)
	{
		m_aiVals.rotation = m_maxRotation;
	}
	else if (-m_aiVals.rotation > m_maxRotation)
	{
		m_aiVals.rotation = -m_maxRotation;
	}
	m_aiVals.position = m_aiVals.position + sf::Vector2f(m_aiVals.velocity.x * dt, m_aiVals.velocity.y * dt);
	m_aiVals.orientation = m_aiVals.orientation + m_aiVals.rotation * dt;

	/*MaxSpeed = 1.0f;
	m_aiVals.velocity = m_ai.getPosition() - m_playerPos;
	m_aiVals.velocity = m_math.normalise(m_aiVals.velocity);
	m_aiVals.velocity = m_aiVals.velocity * MaxSpeed;
	m_aiVals.orientation = getNewOrientation(m_aiVals.orientation, m_aiVals.velocity);*/
}

void AI::init()
{
	setUpAi();
}

void AI::setWander()
{
	m_enemyBehaviour = EnemyBehaviour::WANDER_MAP;
	m_text.setString("Wandering Enemy");
}
void AI::setSeekPlayer()
{
	m_enemyBehaviour = EnemyBehaviour::SEEK_PLAYER;
	m_text.setString("Enemy Seeking Player");
}

void AI::setFlee()
{
	m_enemyBehaviour = EnemyBehaviour::FLEE;
	m_text.setString("Enemy Fleeing Player");

}
void AI::setArrive()
{
	m_enemyBehaviour = EnemyBehaviour::ARRIVE;
	m_text.setString("Enemy Arriving at Player");
}
void AI::setPursue()
{
	m_enemyBehaviour = EnemyBehaviour::PURSUE;
	m_text.setString("Enemy Pursueing Player");
}



void AI::getSteering(sf::Vector2f t_target)
{

	steering.linear = t_target - m_ai.getPosition();
	if (m_enemyBehaviour == EnemyBehaviour::FLEE)
	{
		steering.linear =  m_ai.getPosition() - t_target;
	}
	steering.linear = m_math.normalise(steering.linear);
	steering.linear = steering.linear * m_maxAcelleration;
	steering.angular = 0;
	
}
void AI::setCircleRadius(float t_radius)
{
	m_radius = t_radius;
}



void AI::BoundryControl(sf::VideoMode desktop)
{
	if (m_ai.getPosition().x >= desktop.width + m_0ffset)
	{
		m_ai.setPosition(-50.0f, m_ai.getPosition().y);
	}
	else if (m_ai.getPosition().x <= 0 -m_0ffset)
	{
		m_ai.setPosition(desktop.width, m_ai.getPosition().y);
	}

	else if (m_ai.getPosition().y >= desktop.height + m_0ffset)
	{
		m_ai.setPosition(m_ai.getPosition().x, 0);
	}
	else if (m_ai.getPosition().y <= 0)
	{
		m_ai.setPosition(m_ai.getPosition().x, desktop.height);
	}
}
void AI::setUpAi()
{
	if (!m_font.loadFromFile("FONTS/ariblk.ttf"))
	{
		std::cout << "error with font file file";
	}
	if (!texture.loadFromFile("IMAGES//alien2.png"))
	{
		// error...
	}
	m_text.setString("Test");
	m_text.setFont(m_font);
	m_text.setCharacterSize(25);
	m_text.setFillColor(sf::Color::White); 
	
	m_ai.setTexture(texture);
	m_arrivalRadius = m_player.getCircleRadius();
	m_slowRadius = m_arrivalRadius + 60.0f;
	m_aiVals.position = m_ai.getPosition();
	
}

void AI::pursue(sf::Vector2f t_target, double dt)
{
	m_aiVals.direction = t_target - m_ai.getPosition();
	float vecLength = m_math.length(m_aiVals.direction);
	m_aiVals.distance = vecLength;
	vecLength = m_math.length(m_aiVals.velocity);
	m_aiVals.speed = vecLength;

	if (m_aiVals.speed <= m_aiVals.distance / m_maxTimePrediction)
	{
		m_timePrediction = m_maxTimePrediction;
	}
	else
	{
		m_timePrediction = m_aiVals.distance / m_aiVals.speed;
	}
	sf::Vector2f newTarget = t_target + m_aiVals.velocity * m_timePrediction;
	
	kinematicSeek(newTarget, dt);
	
}
void AI::evade(sf::Vector2f t_target, double dt)
{
	m_aiVals.direction = t_target - m_ai.getPosition();
	float vecLength = m_math.length(m_aiVals.direction);
	m_aiVals.distance = vecLength;
	vecLength = m_math.length(m_aiVals.velocity);
	m_aiVals.speed = vecLength;

	if (m_aiVals.speed <= m_aiVals.distance / m_maxTimePrediction)
	{
		m_timePrediction = m_maxTimePrediction;
	}
	else
	{
		m_timePrediction = m_aiVals.distance / m_aiVals.speed;
	}
	sf::Vector2f newTarget = t_target + m_aiVals.velocity * m_timePrediction;

	kinematicFlee(newTarget, dt);

}

float AI::getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity)
{

	float vecLength = m_math.length(t_velocity);
	if (vecLength > 0)
	{
		return atan2(-m_ai.getPosition().x, m_ai.getPosition().y);
	}
	else
	{
		return t_currentOrientation;
	}
}

void AI::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_ai);
	t_window.draw(m_text);
	t_window.draw(m_rayCast.drawRay());
}

void AI::setTarget(sf::Vector2f t_target)
{
	m_targetVals.position = t_target;

}

float AI::mapToRange(float t_rotation)
{
	return t_rotation = atan2(sin(t_rotation),cos(t_rotation));
}
