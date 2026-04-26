#include "Clicker/Score.h"
#include <TextRenderer.h>

Clicker::Score::Score(float _points)
{
	points = _points;
}

void Clicker::Score::Start()
{
	donutComponent = GetOwner()->GetScene()->FindGameObject("Donut")->GetComponent<Donut>();
	upgradeComponent = GetOwner()->GetScene()->FindGameObject("Donut")->GetComponent<Upgrade>();
}

void Clicker::Score::Update(float _delta_time)
{
	GetOwner()->GetComponent<TextRenderer>()->SetText("Points : " + std::to_string(points));
	bool isClicked = donutComponent->GetIsClicked();
	if (isClicked == true) {
		donutComponent->ToggleIsClicked();
		AddPoints(1 * upgradeComponent->GetUpgradeMultiplier());
		Logger::Log(ELogLevel::Debug, "points : {}", points);
	}
}
