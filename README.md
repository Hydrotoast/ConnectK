Extended ConnectK Shell
=======================

This ConnectK shell decouples the game state from the view in order to enable headless execution as well as AI development independent of the game controller. Please note that this still under significant development.

For the purposes of a tournament shell, all AI must inherit from the `CKPlayer` interface.

Data Structures
---------------

`CKPlayer` Interface which all types of players must implement (including AI)

`BoardState` State of the board which can be cloned for search-tree purposes

`Cell` Structure for `row` and `col` coordinates on a board

`Mark` All possible marks on the board: player A, player B or blank

`BoardConfig` Contains the configuration of the game

