#ifndef KEY_BINDER_H
#define KEY_BINDER_H

#include "stdafx.h"

class KeyBinder
{
public:
   enum class PreSet { ARROWS, WASD, LEET };
   enum class Actions { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT,
                        CHOOSE, PAUSE, NOTHING };
   typedef std::pair<Keyboard::Key, KeyBinder::Actions> BinderPair;   

   KeyBinder(PreSet config = PreSet::ARROWS);
   Actions operator[](Keyboard::Key key) const;
   void setBinding(Keyboard::Key key, Actions action);
   void usePreset(PreSet config);
   PreSet getPreSet() const { return preSet; }
   Keyboard::Key getKeyFromValue(Actions a) const;
   string getKeyStringFromValue(Actions a) const;

private:
   std::map<Keyboard::Key, Actions> keyMap;
   PreSet preSet;
};

#endif