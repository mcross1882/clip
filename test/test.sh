#!/usr/bin/env bash

make

echo "clip Behavior Tests";
echo "---------------------------------------------------------";

# Test stdin copy & paste functionality
echo "- Assert clip copies stdin";

SAMPLE_INPUT="This is a simple test.";

echo $SAMPLE_INPUT | ./clip copy;

SAMPLE_OUTPUT=$(./clip paste);

if [[ "$SAMPLE_INPUT" != "$SAMPLE_OUTPUT" ]]; then
    echo "    - Sample input failed to match clipboard data!";
fi

echo "- Assert clip copies a file";

SAMPLE_FILE="./test/sample.txt";
OUTPUT_FILE="./test/output.out";

./clip copy $SAMPLE_FILE;
./clip paste $OUTPUT_FILE;

if [[ "$(cat $SAMPLE_FILE)" != "$(cat $OUTPUT_FILE)" ]]; then
    echo "    - Sample input file failed to match clipboard data!";
fi

echo "- Assert clip pastes file data to stdout";

if [[ "$(cat $SAMPLE_FILE)" != "$(./clip paste)" ]]; then
    echo "    - Sample input file failed to match clipboard data!";
fi

rm -rf $OUTPUT_FILE;
rm -rf "tmp_buffer";

echo "Tests finished";

