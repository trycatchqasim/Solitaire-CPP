
---

## 🎮 Game Overview

This is a command-line Solitaire game based on the classic Klondike rules. The goal is to move all 52 cards into the four **foundations** (one for each suit), arranged in ascending order from Ace to King.

It features:
- 7 tableau columns
- A stockpile and wastepile
- 4 foundations
- Color-coded suits
- Move validations
- Undo feature
- Console-clearing and color rendering (using ANSI escape codes)

---

## ✨ Features

- 🧱 **OOP Design**: Classes like `Card`, `Suit`, `Stack`, `CardStack`, `DoublyLinkedList`, and `Game`.
- 🃏 **Tableau Setup**: Standard solitaire column-wise face-down and face-up card distribution.
- 🧠 **Move Logic**:
  - Move cards between tableau columns with validation
  - Move cards from tableau/wastepile to foundations
  - Smart rules for opposite color, descending ranks
- 🎨 **Colored Suits**:
  - ♥ Hearts and ♦ Diamonds: Red
  - ♠ Spades and ♣ Clubs: Gray
- ♻️ **Stockpile Cycling**: Automatically reshuffles waste back into the stockpile.
- 🔄 **Undo Functionality**: Revert last move (draw, move, foundation transfers).
- 📜 **Clear UI**: Screen auto-clears after every action for better visibility.

---

## 🎮 How to Play

- Launch the program (see compilation below)
- Choose actions using keys:

| Key | Action |
|-----|--------|
| `s` | Draw from stockpile |
| `m` | Move cards |
| `z` | Undo last move |
| `q` | Quit game |

### 📦 Move Options after `m`:

1. Move between tableau columns  
2. Move waste to tableau  
3. Move waste to foundation  
4. Move column card to foundation  

---

## 🏗️ How It Works

- **Deck creation**: 52 cards from 4 suits (A–K)  
- **Shuffle**: Random shuffle using `srand(time(0))`  
- **Deal**: 7 columns, each increasing in card count, last card face-up  
- **Stockpile**: Remaining cards go to the draw stack  
- **Wastepile**: Shown top card  
- **Foundations**: 4 stacks (one per suit) from Ace to King  
- **Undo**: Maintains command history for reversal

---

## 🧠 Technologies Used

- 💻 C++ (Object-Oriented Programming)
- 🧵 Templates (Generic Stack)
- 🌈 ANSI Escape Codes for coloring
- 🧼 `conio.h` and `system("cls")` for screen clearing
- 🃏 Linked lists for tableau columns

---
