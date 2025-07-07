#include <iostream>
#include <ctime>
#include <conio.h>
using namespace std;  

// Custom Stack Class
template <typename T>
class Stack {
private:
	class Node {
	public:
		T data;
		Node* next;

		Node(const T& value) : data(value), next(nullptr) {}

	};
	Node* top;
	int size;

public:
	Stack() : top(nullptr), size(0) {}

	~Stack() {
		while (!empty()) {
			pop();
		}
	}

	void push(const T& value) {
		Node* newNode = new Node(value);
		newNode->next = top;
		top = newNode;
		size++;
	}

	T pop() {
		if (empty()) {
			throw runtime_error("Stack is empty");
		}
		Node* temp = top;
		T value = temp->data;
		top = top->next;
		delete temp;
		size--;
		return value;
	}

	T& peek() const {
		if (empty()) {
			throw runtime_error("Stack is empty");
		}
		return top->data;
	}

	bool empty() const {
		return top == nullptr;
	}

	int getSize() const {
		return size;
	}
};

// Suit Class
class Suit {
private:
	string name;
	string symbol;
	string color;

public:
	Suit(string n = "", string s = "", string c = "") : name(n), symbol(s), color(c) {}

	bool operator==(const Suit& other) const {
		return name == other.name;
	}

	string getName() const { return name; }
	string getSymbol() const { return symbol; }
	string getColor() const { return color; }

	static const Suit HEARTS;
	static const Suit SPADES;
	static const Suit CLUBS;   
	static const Suit DIAMONDS;
};

const Suit Suit::HEARTS = Suit("Hearts", "(H)", "\033[31m");
const Suit Suit::SPADES = Suit("Spades", "(S)", "\033[90m");
const Suit Suit::CLUBS = Suit("Clubs", "(C)", "\033[90m");
const Suit Suit::DIAMONDS = Suit("Diamonds", "(D)", "\033[31m");
const string rank_names[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

// Card Class
class Card {
public:
	Suit suit;
	int rank;
	bool face_up;

	Card() : suit(Suit::HEARTS), rank(1), face_up(false) {}
	Card(Suit s, int r, bool face_up = false) : suit(s), rank(r), face_up(face_up) {}

	string getCard() const {
		return suit.getColor() + rank_names[rank - 1] + suit.getSymbol() + "\033[0m";
	}

	bool isRed() const {
		return suit.getName() == "Hearts" || suit.getName() == "Diamonds";
	}

	bool isOppositeColor(const Card& other) const {
		return (isRed() && !other.isRed()) || (!isRed() && other.isRed());
	}

	bool canMoveOn(const Card& other) const {
		return other.rank == rank + 1 && isOppositeColor(other);
	}
};

// Node Class for Doubly Linked List
class Node {
public:
	Card card;
	Node* next;
	Node* prev;

	Node(const Card& c) : card(c), next(nullptr), prev(nullptr) {}
};

// Doubly Linked List Class 
class DoublyLinkedList {
private:
	Node* head;
	Node* tail;

public:
	DoublyLinkedList() : head(nullptr), tail(nullptr) {}

	void addCard(const Card& card) {
		Node* newNode = new Node(card);
		if (!head) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}

	bool isEmpty() const {
		return head == nullptr;
	}

	Node* getTail() const {
		return tail;
	}

	void removeTail() {
		if (tail) {
			Node* temp = tail;
			if (tail->prev) {
				tail = tail->prev;
				tail->next = nullptr;
			}
			else {
				head = tail = nullptr;
			}
			delete temp;
		}
	}

	void printList() const {
		Node* current = head;
		while (current) {
			if (current->card.face_up) {

				cout << current->card.getCard() << " ";

			}
			else {

				cout << "[  ] ";

			}
			current = current->next;

		}
		cout << endl;
	}
};

// CardStack Class
class CardStack {
private:
	Stack<Card> cards;

public:
	void push(const Card& card) {
		cards.push(card);
	}

	Card pop() {
		return cards.pop();
	}

	Card peek() const {
		return cards.peek();
	}

	bool isEmpty() const {
		return cards.empty();
	}

	void printStack() const {
		if (!cards.empty()) {
			cout << cards.peek().getCard() << endl;
		}
		else {
			cout << "Empty" << endl;
		}
	}
};

// Command Class 
class Command {
public:
	string type;
	int src, dest, num;

	Command(string t, int s, int d, int n) : type(t), src(s), dest(d), num(n) {}
};

// Game Class
class Game {
private:
	DoublyLinkedList tableau[7];
	CardStack foundations[4];
	CardStack stockpile, wastepile;
	Stack<Command> commandHistory;
	Card deck[52];
	int deckSize;

public:
	Game() : deckSize(0) {
		setupNewGame();
	}

	void setupNewGame() {
		createDeck();
		shuffleDeck();
		dealCardsToTableau();
	}

	void createDeck() {
		deckSize = 0;
		Suit suits[] = { Suit::HEARTS, Suit::SPADES, Suit::CLUBS, Suit::DIAMONDS };
		for (const Suit& s : suits) {
			for (int r = 1; r <= 13; ++r) {
				deck[deckSize++] = Card(s, r);
			}
		}
	}

	void shuffleDeck() {
		srand(time(0));
		for (int i = deckSize - 1; i > 0; --i) {
			int j = rand() % (i + 1);
			swap(deck[i], deck[j]);
		}
	}

	void dealCardsToTableau() {
		int index = 0;
		for (int i = 0; i < 7; ++i) {
			for (int j = 0; j <= i; ++j) {
				deck[index].face_up = (j == i);
				tableau[i].addCard(deck[index++]);
			}
		}

		// Remaining cards go to stockpile
		while (index < deckSize) {
			stockpile.push(deck[index++]);
		}
	}

	void printGameState() const {
		cout << "\033[0;44m";
		cout << "---------------------------------------------------------------------------------------------------------------------\033[0m" << endl;
		cout << "\033[0;44m                                    WELCOME TO SOLITAIRE (MADE BY: QASIM SHAKIL)                                     \033[0m" << endl;
		cout << "\033[0;44m---------------------------------------------------------------------------------------------------------------------\033[0m" << endl;


		cout << "\033[0;32m";
		cout << "\n---------" << endl;
		cout << "TABLEAUS:" << endl;
		cout << "---------\033[0m" << endl;

		for (int i = 0; i < 7; ++i) {

			cout << "\033[0;33mColumn " << i + 1 << ":\033[0m ";

			tableau[i].printList();
		}
		cout << "\033[0;32m";
		cout << "\n------------ " << endl;
		cout << "Foundations: " << endl;
		cout << "------------\033[0m" << endl;
		for (int i = 0; i < 4; ++i) {
			cout << "\033[0;33mFoundation " << i + 1 << ":\033[0m ";
			foundations[i].printStack();
		}
		cout << "\033[0;32m";
		cout << "\n----------------" << endl;
		cout << "STACKS OF CARDS:" << endl;
		cout << "----------------\033[0m" << endl;
		cout << "\033[0;33mStockpile: \033[0m";
		if (!stockpile.isEmpty()) {
			cout << "[  ]" << endl;
		}
		else {
			cout << "Empty" << endl;
		}

		cout << "\033[0;33mWastepile: \033[0m";
		wastepile.printStack();

	}
	void moveCards(int src, int dest, int num_cards) {
		if (src < 1 || src > 7 || dest < 1 || dest > 7 || num_cards <= 0) {
			cout << "Invalid move. Out of bounds." << endl;
			return;
		}

		DoublyLinkedList& fromColumn = tableau[src - 1];
		DoublyLinkedList& toColumn = tableau[dest - 1];

		Node* srcTail = fromColumn.getTail();
		if (!srcTail || !srcTail->card.face_up) {
			cout << "Invalid move. No face-up cards to move." << endl;
			return;
		}

		Card cardsToMove[13];  // Maximum possible cards to move
		int cardsCount = 0;
		for (int i = 0; i < num_cards; i++) {
			if (!srcTail || !srcTail->card.face_up) {
				cout << "Invalid move. Not enough face-up cards to move." << endl;
				return;
			}
			cardsToMove[cardsCount++] = srcTail->card;
			srcTail = srcTail->prev;
		}

		Node* destTail = toColumn.getTail();
		if (destTail && !cardsToMove[cardsCount - 1].canMoveOn(destTail->card)) {
			cout << "Invalid move. Cards don't match move rules." << endl;
			return;
		}

		for (int i = cardsCount - 1; i >= 0; --i) {
			toColumn.addCard(cardsToMove[i]);
			fromColumn.removeTail();
		}

		// Reveal the card in the source column if it exists
		Node* newSrcTail = fromColumn.getTail();
		if (newSrcTail && !newSrcTail->card.face_up) {
			newSrcTail->card.face_up = true;
		}

		cout << "Moved " << num_cards << " card(s) from column " << src << " to column " << dest << endl;
		commandHistory.push(Command("m", src, dest, num_cards));
	}
	bool moveToFoundation(int src) {
		if (src < 1 || src > 7 || tableau[src - 1].isEmpty()) {
			return false;
		}

		Node* topNode = tableau[src - 1].getTail();
		Card topCard = topNode->card;

		for (int i = 0; i < 4; ++i) {
			if ((foundations[i].isEmpty() && topCard.rank == 1) ||
				(!foundations[i].isEmpty() && topCard.suit == foundations[i].peek().suit &&
					topCard.rank == foundations[i].peek().rank + 1)) {
				foundations[i].push(topCard);
				tableau[src - 1].removeTail();

				// Reveal the card in the source column if it exists
				Node* newSrcTail = tableau[src - 1].getTail();
				if (newSrcTail && !newSrcTail->card.face_up) {
					newSrcTail->card.face_up = true;
				}

				commandHistory.push(Command("f", src, i + 1, 1));
				return true;
			}
		}

		return false;
	}

	bool checkWinCondition() const {
		for (int i = 0; i < 4; ++i) {
			if (foundations[i].isEmpty() || foundations[i].peek().rank != 13) {
				return false;
			}
		}
		return true;
	}

	bool moveWasteToTableau(int destColumn) {
		if (wastepile.isEmpty()) {
			cout << "Wastepile is empty." << endl;
			return false;
		}

		Card wasteCard = wastepile.peek();
		DoublyLinkedList& destColumnList = tableau[destColumn - 1];

		Node* destTail = destColumnList.getTail();
		if (!destTail) {
			if (wasteCard.rank == 13) {
				destColumnList.addCard(wasteCard);
				wastepile.pop();
				commandHistory.push(Command("w", -1, destColumn, 1));
				return true;
			}
			cout << "Invalid move. Only a King can be placed in an empty column." << endl;
		}
		else if (wasteCard.canMoveOn(destTail->card)) {
			destColumnList.addCard(wasteCard);
			wastepile.pop();
			commandHistory.push(Command("w", -1, destColumn, 1));
			return true;
		}

		cout << "Invalid move from wastepile to column." << endl;
		return false;
	}

	bool moveWasteToFoundation() {
		if (wastepile.isEmpty()) {
			cout << "Wastepile is empty." << endl;
			return false;
		}

		Card wasteCard = wastepile.peek();

		for (int i = 0; i < 4; ++i) {
			CardStack& foundation = foundations[i];

			if (foundation.isEmpty()) {
				if (wasteCard.rank == 1) {
					foundation.push(wastepile.pop());
					commandHistory.push(Command("f", -1, i + 1, 1));
					return true;
				}
			}
			else if (wasteCard.suit == foundation.peek().suit && wasteCard.rank == foundation.peek().rank + 1) {
				foundation.push(wastepile.pop());
				commandHistory.push(Command("f", -1, i + 1, 1));
				return true;
			}
		}

		cout << "Invalid move to foundation." << endl;
		return false;
	}
	void undoLastMove() {
		if (commandHistory.empty()) {
			cout << "No moves to undo." << endl;
			return;
		}

		Command lastCommand = commandHistory.pop();

		switch (lastCommand.type[0]) {
		case 'm': // Move between tableau columns
			for (int i = 0; i < lastCommand.num; ++i) {
				tableau[lastCommand.src - 1].addCard(tableau[lastCommand.dest - 1].getTail()->card);
				tableau[lastCommand.dest - 1].removeTail();
			}
			// Flip the card in the source column back to face down if it was revealed by the move
			if (!tableau[lastCommand.src - 1].isEmpty()) {
				Node* srcTail = tableau[lastCommand.src - 1].getTail();
				if (srcTail->prev && srcTail->prev->card.face_up) {
					srcTail->prev->card.face_up = false;
				}
			}
			break;

		case 's': // Draw from stockpile
			if (!wastepile.isEmpty()) {
				Card card = wastepile.pop();
				card.face_up = false; // Card goes back to stockpile face down
				stockpile.push(card);
			}
			break;

		case 'w': // Move from waste to tableau
			if (lastCommand.dest > 0) { // Waste to tableau
				Card card = tableau[lastCommand.dest - 1].getTail()->card;
				tableau[lastCommand.dest - 1].removeTail();
				wastepile.push(card);
			}
			break;

		case 'f': // Move to foundation
			if (lastCommand.src == -1) { // Waste to foundation
				if (!foundations[lastCommand.dest - 1].isEmpty()) {
					Card card = foundations[lastCommand.dest - 1].pop();
					wastepile.push(card);
				}
			}
			else { // Tableau to foundation
				if (!foundations[lastCommand.dest - 1].isEmpty()) {
					Card card = foundations[lastCommand.dest - 1].pop();
					tableau[lastCommand.src - 1].addCard(card);
					// Flip the card underneath back to face down if it was revealed by the move
					Node* srcTail = tableau[lastCommand.src - 1].getTail();
					if (srcTail->prev && srcTail->prev->card.face_up) {
						srcTail->prev->card.face_up = false;
					}
				}
			}
			break;
		}

		cout << "Undid last move." << endl;
	}
	void drawCard() {
		if (stockpile.isEmpty()) {
			while (!wastepile.isEmpty()) {
				Card card = wastepile.pop();
				card.face_up = false;
				stockpile.push(card);
			}
			cout << "Recycling wastepile back into stockpile." << endl;
		}
		else {
			Card card = stockpile.pop();
			card.face_up = true;
			wastepile.push(card);
			cout << "Drew card: " << card.getCard() << endl;
		}
		commandHistory.push(Command("s", -1, -1, -1));
	}

	void playGame() {
		printGameState();

		while (true) {

			cout << "\n\033[0;35mChoose action - (s)stockpile, (m)move, (z)undo, (q)quit: \033[0m";
			char action;
			cin >> action;

			if (action == 'q') {
				cout << "Quitting the game..." << endl;
				break;
			}
			else if (action == 's') {
				drawCard();
			}
			else if (action == 'm') {
				char moveType;
				cout << "\033[0;36mChoose move type - (1) Column to Column, (2) Waste to Column, (3) Waste to Foundation, (4) Column to Foundation: \033[0m";
				cin >> moveType;

				if (moveType == '1') {
					int src, dest, num;
					cout << "\033[0;35mMove from column: \033[0m";
					cin >> src;
					cout << "\033[0;35mMove to column: \033[0m";
					cin >> dest;
					cout << "\033[0;35mNumber of cards: \033[0m";
					cin >> num;
					moveCards(src, dest, num);
				}
				else if (moveType == '2') {
					int dest;
					cout << "Move wastepile card to column: ";
					cin >> dest;
					if (!moveWasteToTableau(dest)) {
						cout << "Invalid move from wastepile to column." << endl;
					}
				}
				else if (moveType == '3') {
					// Move wastepile card to a foundation
					if (!moveWasteToFoundation()) {
						cout << "Invalid move from wastepile to foundation." << endl;
					}
				}
				else if (moveType == '4') {
					// Move from column to foundation
					int src;
					cout << "Move to foundation from column: ";
					cin >> src;
					if (!moveToFoundation(src)) {
						cout << "Invalid move to foundation." << endl;
					}
				}
				else {
					cout << "Invalid move type." << endl;
				}
			}
			else if (action == 'z') {
				// Undo last move
				undoLastMove();
			}
			system("cls");  //clears screen
			printGameState();

			if (checkWinCondition()) {
				cout << " CONGRATULATIONS! YOU WON THE GAME! " << endl;
				break;
			}

		}
	}
};

int main() {
	Game game;
	game.playGame();
	return 0;
}
