<div align="left">

<img src="https://github.com/ayogun/42-project-badges/blob/main/badges/push_swapm.png?raw=true" width="150px" alt="Push Swap Badge" style="margin-bottom: 20px;">

<h3>
    <span style="font-family: sans-serif; color: #333;">
        PUSH_SWAP: ALGORITHMIC SORTING ENGINE
    </span>
</h3>
<p>
    <em>42 Lausanne, Switzerland</em>
</p>

<br>

<h3>01. ABOUT</h3>
<p style="max-width: 600px; line-height: 1.6; font-family: sans-serif;">
    This project is a deep dive into algorithmic complexity and stack manipulation. The goal is simple: sort a random set of integers using two stacks (<strong>Stack A</strong> and <strong>Stack B</strong>) and a specific set of operations. The challenge lies in the constraint: minimizing the number of instructions.
    <br><br>
    I implemented the <strong>Turk Algorithm</strong> (Mechanical Turk). Instead of recursive methods like QuickSort, this is a greedy algorithm that calculates the "cheapest" move for every node at every step, ensuring highly optimized operation counts for large datasets.
</p>

<br>
<hr style="height: 2px; border: none; background-color: #000;">
<br>

<h3>02. THE LOGIC</h3>
<table>
    <tr>
        <td width="50%" valign="top">
            <strong>PHASE 1: PARTITIONING</strong>
            <br><br>
            <ul>
                <li><strong>Push to B:</strong> Move all nodes from A to B, leaving only 3 elements.</li>
                <li><strong>Pre-sorting:</strong> While pushing, I check median values. If a node is smaller than the median, I rotate B to place it at the bottom.</li>
                <li><strong>Tiny Sort:</strong> Instantly sort the remaining 3 numbers in Stack A.</li>
            </ul>
        </td>
        <td width="50%" valign="top">
             <strong>PHASE 2: MECHANICAL TURK</strong>
             <br><br>
            <ul>
                <li><strong>Cost Calculation:</strong> For every node in B, I calculate the moves required to put it in position in A.</li>
                <li><strong>Cheapest Move:</strong> I select the node with the absolute lowest cost.</li>
                <li><strong>Simultaneous Rotation:</strong> I utilize <code>rr</code> and <code>rrr</code> to move both stacks at once, saving instructions.</li>
            </ul>
        </td>
    </tr>
</table>

<br>
<br>

<h3>03. TECHNOLOGY STACK</h3>

<p>
    <a href="#">
        <img src="https://img.shields.io/badge/C-000000?style=for-the-badge&logo=c&logoColor=white" alt="C">
    </a>
    <a href="#">
        <img src="https://img.shields.io/badge/Make-000000?style=for-the-badge&logo=gnu-make&logoColor=white" alt="Makefile">
    </a>
    <a href="#">
        <img src="https://img.shields.io/badge/Shell_Script-000000?style=for-the-badge&logo=gnu-bash&logoColor=white" alt="Bash">
    </a>
    <a href="#">
        <img src="https://img.shields.io/badge/Git-000000?style=for-the-badge&logo=git&logoColor=white" alt="Git">
    </a>
</p>

<br>
<hr style="height: 1px; border: none; background-color: #ddd;">
<br>

<h3>04. PERFORMANCE METRICS</h3>

<table>
    <thead align="left">
        <tr>
            <th width="20%">Stack Size</th>
            <th width="40%">Constraint (Max Ops)</th>
            <th width="40%">My Algorithm (Avg Ops)</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td><strong>3 Numbers</strong></td>
            <td>< 3</td>
            <td><strong>1-2</strong> (Hardcoded)</td>
        </tr>
        <tr>
            <td><strong>5 Numbers</strong></td>
            <td>< 12</td>
            <td><strong>9</strong> (Average)</td>
        </tr>
        <tr>
            <td><strong>100 Numbers</strong></td>
            <td>< 700</td>
            <td><strong>~580</strong></td>
        </tr>
        <tr>
            <td><strong>500 Numbers</strong></td>
            <td>< 5500</td>
            <td><strong>~4800</strong></td>
        </tr>
    </tbody>
</table>

<br>
<br>

<h3>05. USAGE</h3>

<p style="font-family: sans-serif;">
Clone the repository and compile the executable using the Makefile:
</p>

```bash
git clone git@github.com:Xabieriribar/push_swap.git
cd push_swap
make

<p style="font-family: sans-serif;"> Run the program with a list of integers: </p>
Bash

./push_swap 4 67 3 87 23

<p style="font-family: sans-serif;"> <strong>Bonus:</strong> Check the number of operations: </p>
Bash

ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l

<h3>06. FILE STRUCTURE</h3> <blockquote> <em>The project follows a strict 42-Norminette compliant structure, separating operations, sorting logic, and parsing utilities.</em> </blockquote>

<h3>07. CONTACT</h3>

<p> <a href="https://ch.linkedin.com/in/xabier-iribar-revuelta-b85b09320" target="_blank"> <img src="https://img.shields.io/badge/LinkedIn-000000?style=for-the-badge&logo=linkedin&logoColor=white" alt="LinkedIn"> </a> <a href="https://xabieriribar.com" target="_blank"> <img src="https://img.shields.io/badge/Portfolio-000000?style=for-the-badge&logo=firefox&logoColor=white" alt="Portfolio"> </a> <a href="mailto:xabieriribarrevuelta@gmail.com"> <img src="https://img.shields.io/badge/Email-000000?style=for-the-badge&logo=gmail&logoColor=white" alt="Email"> </a> </p>

<p style="font-size: 12px; color: #666; margin-top: 20px;"> © 2024 Xabier Iribar Revuelta. All Rights Reserved. </p>

</div>
