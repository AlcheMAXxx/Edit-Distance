# Edit Ditance


## Code Overview

### Data Structures

- **Node**: Represents a node in the BK-Tree, storing a word and links to other nodes.
- **RT**: The root node of the BK-Tree.
- **tree**: A vector storing all nodes of the BK-Tree.
- **ptr**: An index used to track the current node in the tree.

### Functions

- **editDistance**: Computes the edit distance between two words using dynamic programming.
- **add**: Adds a new node to the BK-Tree.
- **getSimilarWords**: Finds and returns words in the dictionary that are within the specified edit distance from the input word.

### Main Function

1. Reads words from `input.txt` into a vector.
2. Adds each word from the vector to the BK-Tree.
3. Prompts the user for an input word and tolerance level.
4. Finds and displays words from the dictionary that are similar to the input word based on the specified tolerance level.

## Contributing

Contributions are welcome! Please fork the repository and submit pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
