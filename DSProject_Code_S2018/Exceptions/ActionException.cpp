#include "ActionException.h"

ActionException::ActionException(ACTION act) {
	exceptionAction = act;
}


ACTION ActionException::getExceptionAction() const {
	return exceptionAction;
}