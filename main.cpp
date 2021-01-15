// Inscreva-se no meu canal oficial: https://youtube.com/channel/UCbtwrr_-iUiRWqjkMpk8g9w?sub_confirmation=1
#include<SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>

using namespace std;
using namespace sf;

int main(){
	Font fonte;
	Text texto;
	fonte.loadFromFile("comic.ttf");
	texto.setFont(fonte);
	texto.setFillColor(Color::White);
	texto.setOutlineThickness(2);
	texto.setOutlineColor(Color::Cyan);
	texto.setPosition(20,515);
	
	char text[60]; 
	int point;
	float raio, velocidade;
	cout << "Digite o numero de circulos: ";
	cin >> point;
	cout << "Digite o raio dos circulos: ";
	cin >> raio;
	cout << "Digite a velocidade: ";
	cin >> velocidade;
	vector<CircleShape> c(point);
	srand(time(NULL));
	for(int i=0; i<c.size(); i++){
		c[i].setPosition(Vector2f(rand()%800, rand()%600));
		c[i].setOrigin(raio,raio);
		c[i].setFillColor(Color(rand()%256,rand()%256,rand()%256));
		c[i].setRadius(raio);
	}

	vector<float> x(point), y(point);
	for(int i=0; i<point; i++){
		x[i]=velocidade*(rand()%2==0)?1:-1;
		y[i]=velocidade*(rand()%2==0)?1:-1;

	}


	RenderWindow window(VideoMode(800,600,32), "SFML");
	window.setFramerateLimit(60);
	bool ok=false;


	ConvexShape triangulo;
	triangulo.setPointCount(point);
	triangulo.setFillColor(Color::Transparent);
	triangulo.setOutlineColor(Color::Yellow);
	triangulo.setOutlineThickness(2);


	while(window.isOpen()){
		Event e;
		while(window.pollEvent(e)){
			if(e.type == Event::Closed){
				Image imagem=window.capture();
				imagem.saveToFile("imagem.png");
				window.close();
			}
			if(e.type == Event::MouseButtonPressed){
                if(Mouse::isButtonPressed(Mouse::Left)){
                    CircleShape c1;
                    c1.setFillColor(Color(rand()%256,rand()%256,rand()%256));
                    c1.setOrigin(raio,raio);
                    c1.setRadius(raio);
                    c1.setPosition(Vector2f(Mouse::getPosition(window).x,Mouse::getPosition(window).y));
                    c.push_back(c1);
                    x.push_back(velocidade*(rand()%2==0)?1:-1);
                    y.push_back(velocidade*(rand()%2==0)?1:-1);
                }
                else if(Mouse::isButtonPressed(Mouse::Right)){
                	c.pop_back();
                	x.pop_back();
                	y.pop_back();
				}
			}
			if(e.type == Event::KeyPressed){
                if(Keyboard::isKeyPressed(Keyboard::Up))
                    raio++;
                if(raio>50) raio=50;
                if(Keyboard::isKeyPressed(Keyboard::Down))
                    raio--;
                if(raio<1) raio=1;
                for(int i=0; i<c.size(); i++){
                    c[i].setRadius(raio);
                    c[i].setOrigin(raio,raio);
                }
                if(Keyboard::isKeyPressed(Keyboard::C))
            		c.erase(c.begin(),c.end());
				
				if(Keyboard::isKeyPressed(Keyboard::Right))
					velocidade+=0.1;
				else if(Keyboard::isKeyPressed(Keyboard::Left))
					velocidade-=0.1;
				if(velocidade<1) velocidade=1;
				if(velocidade>12) velocidade=12;
			}
		}
		if(!window.isOpen()) continue;
		float angulo;
		for(int i=0; i<c.size(); i++){
			for(int j=0; j<c.size(); j++){
				if(j==i) continue;
				if(sqrt(pow(c[i].getPosition().x-c[j].getPosition().x,2)+pow(c[i].getPosition().y-c[j].getPosition().y,2)) <= c[i].getRadius()+c[j].getRadius()){
					x[i]=c[i].getPosition().x;
					y[i]=c[i].getPosition().y;
					angulo = atan2(x[i]-c[j].getPosition().x,y[i]-c[j].getPosition().y);
					x[i] = sin(angulo) * velocidade;
					y[i] = cos(angulo) * velocidade;
				}

			}
		}

		for(int i=0; i<c.size(); i++){
			if(c[i].getPosition().x>=800){
				c[i].setPosition(Vector2f(800,c[i].getPosition().y));
				x[i]*=-1;
			}
			if(c[i].getPosition().y>=600){
				c[i].setPosition(Vector2f(c[i].getPosition().x,600));
				y[i]*=-1;
			}
			if(c[i].getPosition().x<=0){
				c[i].setPosition(Vector2f(0,c[i].getPosition().y));
				x[i]*=-1;
			}
			if(c[i].getPosition().y<=0){
				c[i].setPosition(Vector2f(c[i].getPosition().x,0));
				y[i]*=-1;
			}
		}

		if(!ok){
			for(int i=0; i<c.size(); i++){
				c[i].move(x[i],y[i]);
				triangulo.setPoint(i,c[i].getPosition());
			}
		}
		sprintf(text,"Quantidade de bolinhas: %d\nRaio: %.f Velocidade: %.1f\n",c.size(),raio,velocidade);
		texto.setString(String(text));

		window.clear();
		//window.draw(triangulo);
		for(int i=0; i<c.size(); i++) window.draw(c[i]);
		window.draw(texto);
		window.display();
	}
}
