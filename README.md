This C-based application serves as a command-line program to manage apartment listings in a straightforward way. It allows users to add, remove, and update apartment data, keeping track of properties and their details in an organized manner. Through a series of structured modules, the project handles input/output operations, enforces simple business logic (like price rules or availability checks), and ensures a smooth user experience when interacting with the system.

Specific Explanations

main.c: Acts as the entry point that initializes the program, displays menus, and routes user commands to the appropriate functions.

data.c: Maintains the central data structure holding apartments. It adds new records, searches for existing ones, and updates or deletes them as requested.

logic.c: Enforces any business rules or constraints on apartments, such as pricing guidelines or availability logic, before the data is saved or modified.

interface.c: Manages user interaction, including printing menus, parsing user input, and presenting results. It links user-driven actions (e.g., “add apartment”) to the relevant logic.

utils.c: Provides helper functions (like string manipulation and validation checks) to keep the codebase organized and reduce duplication, ensuring these utilities are accessible to any module that needs them.
