#include "observable.h"

int main()
{
    Observable observable;
    Warning warning;
    Error error;
    FatalError fatalerror;

    observable.AddObserver(&warning);
    observable.AddObserver(&error);
    observable.AddObserver(&fatalerror);
    observable.CallWarning("Warning");
    observable.CallError("Error");
    observable.CallFatalError("FatalError");

    observable.RemoveObserver(&error);
    observable.CallError("Dont remove");
}