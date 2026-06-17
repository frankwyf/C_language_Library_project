# Legacy Merge Notes

This note records what was reviewed under `Local_Legacy/` and how the repository was cleaned for open-source publication.

## What Was Reviewed

- `Local_Legacy/code/`: previous snapshot of the same library project.
- `Local_Legacy/example/`: unrelated customer/order exercise.
- `Local_Legacy/library/`: prototype implementation variant.
- `Local_Legacy/rwtxt/`: text file read/write practice snippets.
- `Local_Legacy/CWK1.docx`, `Local_Legacy/FAQs CWK1.doc`, `Local_Legacy/Demo_CWK1.mp4`: coursework artifacts.

## Merge Decision

- Kept current root version as the primary codebase.
- Normalized file casing for cross-platform compilation (`interface.*`, `user_management.*`).
- Preserved representative sample data while removing personal/sensitive identifiers.

## Cleanup Decision

The following legacy assets are removed from the active open-source tree because they are either duplicate, unrelated, or private coursework context:

- Entire `Local_Legacy/` tree
- Historical screenshot folder used only for coursework submission
- Redundant Linux text-file copies used for earlier line-ending workaround

## Why

The goal is a clean, minimal, portfolio-grade repository with:

- one active code path
- clear open-source documentation
- no personal credentials or private school submission files
