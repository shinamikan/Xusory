#pragma once

class IScript
{
public:
	virtual ~IScript() = default;
	virtual void Start() = 0;
	virtual void Update() = 0;
};
