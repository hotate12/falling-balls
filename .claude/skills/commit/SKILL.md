---
name: commit
description: Create a git commit following the Lucent Commits policy (Conventional Commits)
user-invocable: true
---

# Lucent Commits — Commit Workflow

Generate and execute a git commit strictly following the **Lucent Commits** specification.

## Procedure

1. **Load policy**: Read `.claude/policies/commit-message.toml` for the current specification version and rules.
2. **Inspect changes**:
   - Run `git diff --staged` to analyze staged changes.
   - If nothing is staged, run `git diff` and `git status` to report the situation to the user. Do not proceed without staged changes.
3. **Select mode**:
   - **concise** (default): Focused changes in a single domain. Maximize signal density.
   - **structured**: Changes spanning multiple domains requiring grouped rationale.
4. **Compose message** per the loaded policy:
   - Subject line: `<type>(<optional_scope>): <subject>` — max 50 characters, imperative mood, lowercase, no trailing punctuation.
   - Allowed types: `feat`, `fix`, `refactor`, `perf`, `style`, `docs`, `test`, `build`, `ci`, `chore`.
   - Scope: Only for strictly localized changes. Omit if changes span multiple areas or scope would exceed the 50-character limit.
   - Body: 72-char line limit, bullets with `- `, mandatory empty line after subject.
   - Breaking changes: Append `!` after type/scope in subject, add `breaking change:` footer with explicit justification.
   - Tone: Professional native English. Zero filler. Precise engineering terminology.
5. **Present draft** to the user for review before committing.
6. **Execute commit** using the approved message via HEREDOC format.
7. **Verify** with `git log --oneline -1` and `git status`.

## Rules Summary (from policy)

- Subject ≤ 50 characters. Body lines ≤ 72 characters.
- Imperative mood, lowercase, no trailing punctuation.
- Empty line between subject and body is mandatory.
- Avoid quotation marks in body unless required for exact syntax.
- Use `- ` (dash-space) for bullet points.
- In **structured** mode, prefix bullets with a `ScopeHeader:` to group changes by domain.
- The session URL footer is appended after the policy-compliant message body.

$ARGUMENTS
