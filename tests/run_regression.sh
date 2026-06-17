#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT_DIR"

if [[ ! -x ./library ]]; then
  make
fi

TMP_DIR="$(mktemp -d)"
trap 'rm -rf "$TMP_DIR"' EXIT

cp books.txt "$TMP_DIR/books.txt"
cp user.txt "$TMP_DIR/user.txt"
cp loan.txt "$TMP_DIR/loan.txt"

run_case() {
  local name="$1"
  local input_text="$2"
  local expected_text="$3"

  local output
  output="$(printf "%b" "$input_text" | ./library "$TMP_DIR/books.txt" "$TMP_DIR/user.txt" "$TMP_DIR/loan.txt" 2>&1 || true)"

  if ! grep -Fq "$expected_text" <<<"$output"; then
    echo "[FAIL] $name"
    echo "Expected to find: $expected_text"
    echo "--- Output ---"
    echo "$output"
    exit 1
  fi

  echo "[PASS] $name"
}

run_case "quit_from_main_menu" "5\n" "Goodbye"
run_case "show_books_then_quit" "4\n5\n" "Programming in C"
run_case "invalid_option_then_quit" "x\n5\n" "invalid"
run_case "login_failure_then_quit" "2\nno_user\nbad_pass\n5\n" "invalid"
run_case "librarian_login_then_quit" "2\nadmin\nadmin123\n5\n5\n" "Successfully logged in as Librarian"

# Data consistency case: borrow a book then return it and verify loan data rollback.
cp loan.txt "$TMP_DIR/loan_before.txt"
output_borrow_return="$(printf "%b" "2\nalice\nalice123\n1\n1\n2\n1\n5\n5\n" | ./library "$TMP_DIR/books.txt" "$TMP_DIR/user.txt" "$TMP_DIR/loan.txt" 2>&1 || true)"

if ! grep -Fq "successfuly borrowed" <<<"$output_borrow_return"; then
  echo "[FAIL] borrow_and_return_flow"
  echo "Expected borrow success message"
  echo "--- Output ---"
  echo "$output_borrow_return"
  exit 1
fi

if ! grep -Fq "successfully returned" <<<"$output_borrow_return"; then
  echo "[FAIL] borrow_and_return_flow"
  echo "Expected return success message"
  echo "--- Output ---"
  echo "$output_borrow_return"
  exit 1
fi

if ! cmp -s "$TMP_DIR/loan_before.txt" "$TMP_DIR/loan.txt"; then
  echo "[FAIL] borrow_and_return_flow"
  echo "Loan file was not restored after borrow+return cycle"
  echo "--- Before ---"
  cat "$TMP_DIR/loan_before.txt"
  echo "--- After ---"
  cat "$TMP_DIR/loan.txt"
  exit 1
fi

echo "[PASS] borrow_and_return_flow"

echo "All regression tests passed."
