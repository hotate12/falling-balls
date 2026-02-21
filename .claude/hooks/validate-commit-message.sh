#!/bin/bash
# validate-commit-message.sh
# PreToolUse hook: safety-net validation for Lucent Commits policy.
# Primary enforcement is via the /commit skill and policy TOML.
# This hook catches obvious violations before execution.

set -uo pipefail

INPUT=$(cat)

# Require jq for JSON parsing; pass through if unavailable
command -v jq >/dev/null 2>&1 || exit 0

COMMAND=$(echo "$INPUT" | jq -r '.tool_input.command // empty' 2>/dev/null) || exit 0

# Only intercept git commit commands
echo "$COMMAND" | grep -qE 'git\s+commit' || exit 0

# Skip amend, merge, and no-message commits
echo "$COMMAND" | grep -qE '\-\-(amend|no-edit|allow-empty-message)' && exit 0

# Verify a valid Conventional Commits type prefix appears in the command
TYPES="(feat|fix|refactor|perf|style|docs|test|build|ci|chore)"
if ! echo "$COMMAND" | grep -qE "${TYPES}(\([a-z0-9_-]+\))?!?:\s"; then
  cat >&2 <<'MSG'
[Lucent Commits] Subject must follow: <type>(<scope>): <subject>
Allowed types: feat, fix, refactor, perf, style, docs, test, build, ci, chore.
Read the policy: .claude/policies/commit-message.toml
MSG
  exit 2
fi

exit 0
