# Brand Bond

A C program that simulates a mini social network with users, friends, and brand preferences.  
It includes logic to suggest new friends based on **mutual brands** and handles tricky edge cases.

## Features
- **User & Friend Management**: create users, add/remove friends, free memory safely.  
- **Brand Tracking**: associate brands with users, detect overlaps.  
- **Friend Suggestion**: recommend friends based on most mutual brands, with reverse-alphabetical tie-breaking.  
- **Robust Test Suite**: covers general, edge, and error cases.  

## File Structure
- `social.c` → Core implementation (users, brands, friends, suggestion logic).  
- `main.c` → Test driver with unit tests.  

## Example Run
```bash
gcc main.c social.c -o social
./social
