#!/bin/bash
JSONSTR="'{\"jsonrpc\": \"1.0\", \"id\":\"curltext\", \"method\": \"getblock\", \"params\": [\"$1\"] }'"

eval "curl --silent --user USERNAME:PASSWORD --data-binary "$JSONSTR" -H 'content-type: text/plain;' http://127.0.0.1:9325/ | jq '.result.channel' | nc XXX.XXX.XXX.XXX 80"
