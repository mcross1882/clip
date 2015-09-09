clip
====

An easy to way to perform copy & paste operations in the terminal.

Copy and paste using `stdin/stdout`

```sh
# Copy a single line
echo "This is some data" | clip copy

# Copy lots of data
cat ./sample.txt | clip copy

# Copy a single file
clip copy sample.txt

# Now its time to paste the data...

# Using stdout
clip paste

# Send clipboard data to file
clip paste output.txt
```
