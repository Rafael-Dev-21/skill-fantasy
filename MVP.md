== SKILL FANTASY v0.4.0 (MVP) ==

The purpose of this document is to guide the design, to specify architecture, and to simplify getting help.

1. Vision

> Skill Fantasy is a ASCII based survival sandbox game where the player thrive in a hostile world, using it's creativity and knowledge.

1.1 Genre:
- Survival
- Sandbox
- Roguelike
- RPG

1.2 Target Audience:
- Vim users
- Roguelike fans
- Survival fans
- Automation fans

1.3 Inspirations
- Minecraft
- Ark
- Survival Kids
- Terraria
- Rogue
- Doom
- MUD1
- Pokemon

1.4 Planed Schedule
- MVP (2025/2026)
- Post-MVP
- Classic
- Indev
- Infdev
- Alpha
- Beta
- 1.0.0
- Post-1.0.0

2. World

2.1 MVP

The world is a hash generated 64x64 bidimensional space. Each cell is a tile. A tile can be a resource, a station, a obstacle, a hazard, or plain old nothing. Over the world, there will be distributed sticks, pebbles, bushes, rocks and trees. Each yield different resources according to it's needs and kinds.

Over the world there will also be hares and wolves. Hares seek bushes, competing with the player for them, evade wolves, and and will flee the player when hit. It will have small memory of recent see bushes. Wolves pack hunt, pack defend, will pursue hares for food, and will pursue the player when hit, evading only when low on life.

There will also be the bandit. The bandit is smart. They remember past encounters. They remember past wounds. They change behavior according to the current context. They search, appearing in the world at fixed intervals. Sometimes they act and/or appear outside of schedule. They hunt and take indiscriminately.

2.2 Post-MVP

???

2.3 Infdev

The world will be infinite.

3. Display (Audio-visual)

The game will be rendered using ASCII glyphs. There will be optional colors, but the game should not be dependant on it.

The game will have 7 main musical motifs: dumb, scare, sorrow, action, idle, win and lose. Through the ages the compositions of said motifs will become more refined. For example, dumb at paleolithic will be simple, main melody, ambience and percussion. Going to mesolithic, it gains bass. At neolitic it gains a second voice. After the stone age it loses ambience and begins to gain more structure and instruments as ages pass. At modern age it's a poprock song.

The game will have many sound effects and sound cues. The major part of display design should go to it. Ensure immersion.

@
  That is the player
.
  That is floor
/
  That is a stick
o
  That is a pebble
*
  That is a bush
T
  That is a tree
O
  That is a rock
#
  That is a wall
+
  That is a door
5
  That is a fire
H
  That is a hare
W
  That is a wolf
&
  That is a bandit
%
  That is a body

4. Mechanics

5. Technical

A. Miscellaneous

A.1 Terms

Seek = go after something
Flee = go opposite to something
Wander = change direction slightly from time to time
Pursue = go after the probable future position of something (primitive kind of prediction)
Evade = go opposite to the future position of something
Follow = seek after determinated path

---------

@rayquazaboladao (YouTube)
Rafael-Dev-21 (GitHub)

(cc) Victor Rafael Pereira Alves, cc-by-sa 4.0