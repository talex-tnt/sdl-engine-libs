# CppUtils
C++ Utilities: basic utility library in C++

### Identifier
It creates a new domain of identifiers that share the same basic type (e.g. int, string, char):
```c++
DEFINE_IDENTIFIER(PlayerId, std::uint32_t);
DEFINE_IDENTIFIER(PlayerName, std::string);
DEFINE_IDENTIFIER(PlayerLevel, std::uint32_t);
```
these identifiers are meant to be used when designing and implementing new APIs that require/provide information about some specific domain. 

Here's an example:

```c++
class PlayerDef
{
public:
  PlayerId GetId() const { return m_id; }
  const PlayerName& GetName() const& { return m_name; }
// other stuff ...
private:
  PlayerId m_id;
  PlayerName m_name;
}

class PlayerState
{
public:
  PlayerId GetId() const { return m_id; }
  PlayerLevel GetCurrentLevel() const { return m_currentLevel; }
  // ...
private:
  PlayerId m_id;
  PlayerLevel m_currentLevel;
}


const PlayerDef& FindPlayerDef(PlayerId i_id);
const PlayerState& FindPlayerState(PlayerId i_id);


class PlayerWidget
{
public:
  using OnSelectSig = utils::Signal<PlayerId>;
  using Connection OnSelectSig::Connection;
  // ...
  PlayerWidget(PlayerId i_playerId, const PlayerName& i_name, PlayerImageId i_playerImageId);
  Connection DoOnSelected(std::function<void(PlayerId>> i_slot);
  // ...
 private:
  PlayerId m_playerId;
  OnSelectSig m_onSelectSignal;
}
```

### Signal-Slots
C++11 Implementation of the Signal-Slot pattern.

It allows to connect Slots (Listeners) to a Signal object (Emitter).

The Signal object can Emit() a signal to notify all the connected listeners.

The Signal's Connect() method returns a (Scoped) Connection object, 
as long as this object exists the connection will exist as well 
(unless the Disconnect() method is called). 

Example:
```c++
int value = 0;

using Sig = utils::Signal<int>;

Sig::Connection c1 = sig.Connect([ &value ] (int delta) { value += delta; });

sig.Emit(100);

EXPECT_EQ(value, 100);

```
