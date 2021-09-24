# skyscraper-solver
Solver written in c++ (and rewritten to c#) that can solve skycrapers of sizes between 4-8. It uses basic logic rules and backtracing algorithm.

# fast indroduction
Basic rules in skyscraper puzzles:
* Every field in the grid and clue must contain a number between 1 and N;
* The clue shows how many skyscarpers are visible from its direction;
* Higher skyscrapers *block* the view of lower skyscrapers located behind them;
* Fields numbers in the same row/column can't repeat (similar rules to the sudoku puzzle);

**More resources:**
* https://www.conceptispuzzles.com/index.aspx?uri=puzzle/skyscrapers/rules
* https://www.puzzlemix.com/rules-skyscraper.php
* https://calcblocks.com/rule-tutorial-skyscrapers-puzzle/#/

# how to use c++ console version
At first, give size of the board and number of clues you'll enter. Then, type these clues by the following model:<br />
`direction location value`<br />
You can type 4 directions (U - Up, R - Right, D - Down, L - Left) with location belongs to the range <1; N> and with value of clues in range <1; N>.

||**5**||**3**|**1**|||
|-|-|-|-|-|-|-|
||||||||
|||||||**1**|
||||||||
|**2**|||||||
|||||||**5**|
||||||**3**||

So, according to the previous example, to *implement* that skycraper, you need to type:<br />
`5`<br />
`7`<br />
`U 1 5`<br />
`U 3 3`<br />
`U 4 1`<br />
`R 2 1`<br />
`R 5 5`<br />
`D 5 3`<br />
`L 4 2`<br /><br />
And how it should look like:<br />
![Imgur](https://i.imgur.com/VkKRFBf.png)
