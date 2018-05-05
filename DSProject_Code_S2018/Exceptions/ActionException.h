#pragma once

#include "../Defs.h"

class ActionException {
	ACTION exceptionAction;
public:
	ActionException(ACTION exceptionAction);
	ACTION getExceptionAction() const;
};
