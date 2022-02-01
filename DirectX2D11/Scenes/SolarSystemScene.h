#pragma once

class SolarSystemScene : public Scene 
{
private:
	TestRect* sun;
	TestRect* earth;
	TestRect* moon;

public:
	SolarSystemScene();
	~SolarSystemScene();

	virtual void Update() override;
	virtual void Render() override;
};