#include "TiledMap.h"
#include "../GameManager/WavesManager.h"
TiledMap::TiledMap()
{
	m_Floor = GConnect->getFloor();
	m_Level = GConnect->getLevel();
	m_Tiles = GConnect->getTiles();
	m_TileBoxes = GConnect->getTileBoxes();
	FOR(i, 0, 9 * RoomMaxSize - 1) {
		FOR(j, 0, 9 * RoomMaxSize - 1) {
			(*m_Tiles)[i][j] = new Tile;
			(*m_Tiles)[i][j]->setPosition(j * TileSize, i * TileSize);
		}
	}
	
	FOR(i, 0, 8) {
		FOR(j, 0, 8) {
			if (i % 2 == 0 && j % 2 == 0) (*m_TileBoxes)[i][j] = new Room;
			else (*m_TileBoxes)[i][j] = new Hall;
		}
	}
	

	m_RoomSize = GConnect->getRoomSize();
	m_RoomPos = GConnect->getRoomPos();

	m_MiniMap = new MiniMap;

	m_RoomActive = GConnect->getRoomActive();

	
	m_TileSet = 0;

	m_Shader = new sf::Shader;
	m_Shader->loadFromFile("Sources/GameManager/tint.frag", sf::Shader::Fragment);//use your own file path
	m_Shader->setUniform("flashColor", sf::Glsl::Vec4(0, 0, 0, 0.5));

	m_Rect = new sf::RectangleShape(sf::Vector2f(50000, 50000));
	
}

TiledMap::~TiledMap()
{
}

void TiledMap::Init()
{
	*m_Floor = 1;
	*m_Level = 0;
	FOR(i, 0, 8) {
		FOR(j, 0, 8) {
			(*m_TileBoxes)[i][j]->Init();
		}
	}
	ChangeMap();
	m_Rect->setPosition(0.f, 0.f);
	m_Rect->setFillColor(sf::Color(0, 0, 0, 10));
	m_currentDeadWait = 0.f;
	m_waitDead = 4.f;
}

sf::IntRect m_IntRect;
float wait;
bool canchange = true;
bool canshoot = true;
void TiledMap::Update(float deltaTime)
{
	m_tempTime += deltaTime;
	if (GConnect->getPlayer()->getHp().x <= 0) {
		m_Rect->setFillColor(sf::Color(255, 255, 255, 255));
		m_currentDeadWait += deltaTime;
		if (m_currentDeadWait >= m_waitDead) {
			GameStateMachine::GetInstance()->PopState();
		}
	}
	if (m_tempTime >= 1.3f && m_PortalStart->Play(deltaTime)) {
		if (PortalStartState == "Open") {
			GConnect->getPlayer()->setActive(true);
			m_PortalStart->Reset(*ASSET->getTexture("Portal/Portal_Idle"), sf::Vector2i(8, 1), 0.1f);
			PortalStartState = "Idle";
		}
		else if (PortalStartState == "Idle") {	
			m_PortalStart->Reset(*ASSET->getTexture("Portal/Portal_Close"), sf::Vector2i(8, 1), 0.1f);
			PortalStartState = "Close";
		}
		else {
			PortalStartState = "End";
		}
	}
	if (m_tempTime >= 1.3f) {
		if (PortalEndState == "Open") {
			m_PortalEnd->Update(deltaTime);
			if (Collision::dist(GConnect->getPlayer()->getHitBox()->getPosition(), m_PortalEnd->getPosition()) <= 50.f) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					GConnect->getPlayer()->setActive(false);
					PortalEndState == "Idle";
					ChangeMap();
				}
			}
		}
		else if (PortalEndState == "Idle") {
			m_PortalEnd->Reset(*ASSET->getTexture("Portal/Portal_Close"), sf::Vector2i(8, 1), 0.1f);
			PortalEndState = "Close";
		}
		else if (PortalEndState == "Close") {
			if (m_PortalEnd->Play(deltaTime)) {
				PortalEndState = "End";
			}
		}
	}
	
		
	/*m_MiniMap->Update(deltaTime, *m_RoomPos);*/
	//printf("%d %d\n", m_RoomPos->x, m_RoomPos->y);
	//if (m_RoomPos->x != -1 && m_RoomPos->y != -1) printf("%d", (*m_TileBoxes)[m_RoomPos->y][m_RoomPos->x]->getActive());
	if (m_RoomPos->x != -1 && m_RoomPos->y != -1 && (*m_TileBoxes)[m_RoomPos->y][m_RoomPos->x]->getActive() == true) {
		if (*m_RoomActive) {

		}
		else {
			*m_RoomActive = true;
			RoomActive(true);
			WManager->RoomActive(true);
		}
	}
	else
	{
		if(*m_RoomActive) RoomActive(false);
		*m_RoomActive = false;
	}
	FOR(i, 0, 8) {
		FOR(j, 0, 8) {
			(*m_TileBoxes)[i][j]->Update(deltaTime);
		}
	}
	//printf("%d\n", *m_RoomActive);
	/*F
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && canchange) {
		canchange = false;
		wait = 0.f;
		Init();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && canchange) {
		canchange = false;
		wait = 0.f;
		if (m_TileSet == 0) m_TileSet = 1;
		else m_TileSet = 0;
	}*/
}

void TiledMap::Render(sf::RenderWindow* window)
{
	/*
	window->draw(*m_drawMap);
	if (*GConnect->getActive()) {
		window->draw(*m_drawDoors);
	}
	*/
	/*
	FOR(i, 0, 8) {
		FOR(j, 0, 8) {
			(*m_TileBoxes)[i][j]->Render(window);
			(*m_Halls)[i][j]->Render(window);		
		}
	}
	*/

	FOR(i, 0, 8) {
		FOR(j, 0, 8) {
			(*m_TileBoxes)[i][j]->Render(window);
		}
	}
	if (m_tempTime >= 1.f && PortalStartState != "End") window->draw(*m_PortalStart);
	if (m_tempTime >= 1.f && PortalEndState != "End") window->draw(*m_PortalEnd);
	window->draw(*m_Rect);
}

void TiledMap::Reset()
{
	FOR(i, 0, 9 * RoomMaxSize - 1) {
		FOR(j, 0, 9 * RoomMaxSize - 1) {
			(*m_Tiles)[i][j]->setType(TileType::TILE_DEFAULT);
		}
	}
	FOR(i, 0, 8) {
		FOR(j, 0, 8) {
			(*m_TileBoxes)[i][j]->setType(TileBoxType::BOX_DEFAULT);
		}
	}
	m_tempTime = 0.f;
	m_PortalStart = new Animation(*ASSET->getTexture("Portal/Portal_Open"), sf::Vector2i(8, 1), 0.1f);
	m_PortalEnd = new Animation(*ASSET->getTexture("Portal/Portal_Idle"), sf::Vector2i(8, 1), 0.1f);
	PortalStartState = "Open";
	PortalEndState = "Open";
	m_currentDeadWait = 0.f;
	m_waitDead = 4.f;
}

int marked[5][5];

stack<pair<int, int>> st;
stack<pair<int, int>> st1;
stack<pair<int, int>> st2;
vector <stack<pair<int, int>>> path;
pair<int, int> Move[4] = { mp(-1,0), mp(0,-1), mp(1,0), mp(0,1) };

void DFS(pair<int, int> end, int MAX) {
	if (MAX == -1) {
		st1.push(st.top());
		st.pop();
		while (!st.empty()) {
			st1.push(st.top());
			if (st.size() > 1) st2.push(st.top());
			st.pop();
		}
		path.push_back(st2);
		while (!st2.empty()) st2.pop();
		while (!st1.empty()) {
			st.push(st1.top());
			st1.pop();
		}
	}
	FOR(i, 0, 3) {

		int x = st.top().first + Move[i].first;
		int y = st.top().second + Move[i].second;

		if (x >= 0 && x < 5 && y >= 0 && y < 5 && marked[y][x] == 0 && (abs(end.first - x) + abs(end.second - y)) <= MAX) {

			st.push(mp(x, y));
			marked[y][x] = 1;
			DFS(end, MAX - 1);
			st.pop();
			marked[y][x] = 0;
		}
	}
}


void TiledMap::ChangeMap()
{
	Reset();
	
	if (*m_Level == 5) {
		if (*m_Floor == 4) {

		}
		else {
			*m_Floor += 1;
			*m_Level = 1;
		}
	}
	else {
		*m_Level += 1;
	}
	vector<TileBox*> rooms;

	(*m_TileBoxes)[4][4]->Create(m_TileSet, TileBoxType::ROOM_START, sf::Vector2i(4, 4));
	rooms.push_back((*m_TileBoxes)[4][4]);
	int endx;
	int endy;
	while (1) {
		endx = random::random(0, 4);
		endy = random::random(0, 4);
		if ((endx + endy) % 2 == (*m_Level != 5 ? 1 : 0) && (*m_TileBoxes)[endy * 2][endx * 2]->getType() == TileBoxType::BOX_DEFAULT) {
			(*m_TileBoxes)[endy * 2][endx * 2]->Create(m_TileSet, *m_Level != 5 ? TileBoxType::ROOM_END : TileBoxType::ROOM_BOSS, sf::Vector2i(endx * 2, endy * 2));
			break;
		}

	}
	
	FOR(i, 0, 4) {
		FOR(j, 0, 4) marked[i][j] = 0;
	}
	marked[2][2] = 1;
	path.clear();
	while (!st.empty()) st.pop();
	st.push(mp(2, 2));

	DFS(mp(endx, endy), *m_Level != 5 ? 2 : 3);

	int choosed = random::random(0, path.size() - 1);

	

	while (!path[choosed].empty()) {
		(*m_TileBoxes)[path[choosed].top().second * 2][path[choosed].top().first * 2]->Create(m_TileSet, TileBoxType::ROOM_NORMAL, sf::Vector2i(path[choosed].top().first * 2, path[choosed].top().second * 2));
		rooms.push_back((*m_TileBoxes)[path[choosed].top().second * 2][path[choosed].top().first * 2]);
		path[choosed].pop();
	}

	rooms.push_back((*m_TileBoxes)[endy * 2][endx * 2]);

	
	FOR(i, 0, rooms.size() - 2) {
		ConnectRooms(rooms[i], rooms[i + 1]);
	}

	if (rooms.size() >= 4) {
		choosed = random::random(1, rooms.size() - 3);
		FOR(i, 0, 3) {
			int x = rooms[choosed]->getPos().x + Move[i].first * 2;
			int y = rooms[choosed]->getPos().y + Move[i].second * 2;
			if (x >= 0 && x < 9 && y >= 0 && y < 9) {
				if ((*m_TileBoxes)[y][x]->getType() == TileBoxType::BOX_DEFAULT) {
					(*m_TileBoxes)[y][x]->Create(m_TileSet, TileBoxType::ROOM_CHEST, sf::Vector2i(x, y));
					ConnectRooms((*m_TileBoxes)[y][x], rooms[choosed]);
					break;
				}
			}
		}
		choosed = random::random(1, rooms.size() - 2);
		if (random::random(0, 3) == 0) {
			FOR(i, 0, 3) {
				int x = rooms[choosed]->getPos().x + Move[i].first * 2;
				int y = rooms[choosed]->getPos().y + Move[i].second * 2;
				if (x >= 0 && x < 9 && y >= 0 && y < 9) {
					if ((*m_TileBoxes)[y][x]->getType() == TileBoxType::BOX_DEFAULT) {
						(*m_TileBoxes)[y][x]->Create(m_TileSet, TileBoxType::ROOM_NORMAL, sf::Vector2i(x, y));
						ConnectRooms((*m_TileBoxes)[y][x], rooms[choosed]);
						break;
					}
				}
				
			}
		}	
	}
	
	
	
	//m_PortalStart->setOrigin(m_PortalStart->getTexture()->getSize().x / 2.f, m_PortalStart->getTexture()->getSize().y / 2.f);
	m_PortalStart->setScale(4.f, 4.f);
	m_PortalStart->setPosition((2 * 2 + 0.5f)* RoomMaxSize* TileSize, (2 * 2 + 0.5f)* RoomMaxSize* TileSize);
	m_PortalEnd->setScale(4.f, 4.f);
	m_PortalEnd->setPosition((endx * 2 + 0.5f)* RoomMaxSize* TileSize, (endy * 2 + 0.5f)* RoomMaxSize* TileSize);
	GConnect->getPlayer()->getHitBox()->setPosition((2 * 2 + 0.5f)* RoomMaxSize* TileSize, (2 * 2 + 0.5f)* RoomMaxSize* TileSize);
	
}

void TiledMap::ConnectRooms(TileBox* room1, TileBox* room2)
{
	if (room1->getPos().x == room2->getPos().x) {
		(*m_TileBoxes)[(room1->getPos().y + room2->getPos().y) / 2][room1->getPos().x]->Create(m_TileSet, TileBoxType::HALL_VERTICAL, sf::Vector2i(room1->getPos().x, (room1->getPos().y + room2->getPos().y) / 2));
	}
	else if (room1->getPos().y == room2->getPos().y) {
		(*m_TileBoxes)[room1->getPos().y][(room1->getPos().x + room2->getPos().x) / 2]->Create(m_TileSet, TileBoxType::HALL_HORIZONTAL, sf::Vector2i((room1->getPos().x + room2->getPos().x) / 2, room1->getPos().y));
	}
}

void TiledMap::RoomActive(bool active)
{
	FOR(i, 0, 8) {
		FOR(j, 0, 8) {
			if (i % 2 == 1 || j % 2 == 1) (*m_TileBoxes)[i][j]->RoomActive(active);
		}
	}
	(*m_TileBoxes)[m_RoomPos->y][m_RoomPos->x]->setActive(active);
}

sf::Vector2i TiledMap::m_getRes()
{
	return sf::Vector2i(*m_Floor, *m_Level);
}




