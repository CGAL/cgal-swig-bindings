# Instructions for Merging PR #295 and Refreshing Dependabot PRs

## Summary
This document provides step-by-step instructions for merging PR #295 and refreshing the dependabot PRs.

## Prerequisites
- You must have write access to the CGAL/cgal-swig-bindings repository
- PR #295 CI checks must be passing

## Step 1: Check PR #295 Status

1. Visit https://github.com/CGAL/cgal-swig-bindings/pull/295
2. Verify that all CI checks have passed (look for green checkmarks)
3. Check that the PR is marked as "Ready for review" (currently it's in Draft state)

### To mark as ready for review:
- Click the "Ready for review" button at the bottom of the PR if it's still in draft state

## Step 2: Review PR #295 Changes

PR #295 makes the following changes:
- Updates CGAL version references from 6.0.1 to 6.1
- Updates branch references from `6.0.x-branch` to `6.1.x-branch` and `master` to `main`
- Fixes macOS matrix exclusions (changes from `macos-14` to `macos-latest`)
- Adds `-DCMAKE_POLICY_VERSION_MINIMUM=3.5` flag to LAStools CMake build to fix compatibility issues

These changes fix GitHub Actions failures related to:
- LAStools build errors on all macOS runners
- Incorrect Python version exclusions for macOS

## Step 3: Merge PR #295

Once CI checks are passing:

###Option A: Using GitHub Web Interface
1. Go to https://github.com/CGAL/cgal-swig-bindings/pull/295
2. Scroll down to the merge section
3. Click "Merge pull request"
4. Confirm the merge

### Option B: Using GitHub CLI
```bash
gh pr merge 295 --auto --squash
```

### Option C: Using Git Command Line
```bash
git fetch origin
git checkout main
git merge --squash origin/copilot/debug-github-actions
git commit -m "Fix GitHub Actions failures: LAStools CMake compatibility and macOS matrix exclusions (#295)"
git push origin main
```

## Step 4: Refresh Dependabot PRs

After merging PR #295, the following dependabot PRs need to be refreshed (rebased on the new main branch):

1. **PR #294**: Bump actions/download-artifact from 4 to 6
   - URL: https://github.com/CGAL/cgal-swig-bindings/pull/294
   
2. **PR #293**: Bump actions/upload-artifact from 4 to 5
   - URL: https://github.com/CGAL/cgal-swig-bindings/pull/293
   
3. **PR #292**: Bump actions/setup-python from 5 to 6
   - URL: https://github.com/CGAL/cgal-swig-bindings/pull/292
   
4. **PR #290**: Bump actions/checkout from 4 to 5
   - URL: https://github.com/CGAL/cgal-swig-bindings/pull/290

### To refresh each PR:

**Option A: Comment-based refresh (recommended)**
For each PR, add the following comment:
```
@dependabot rebase
```

This will trigger Dependabot to rebase the PR on the current main branch.

**Option B: Recreate the PR**
For each PR, add the following comment:
```
@dependabot recreate
```

This will recreate the PR from scratch with the latest changes.

**Option C: Close and let Dependabot recreate automatically**
Close each PR and Dependabot will automatically recreate them after a short delay.

## Verification

After completing all steps:
1. Verify that PR #295 is merged into main
2. Check that all dependabot PRs show green CI checks after rebasing
3. Consider merging the dependabot PRs if they pass CI

## Automation Note

These steps require manual intervention because they involve:
- Merging pull requests
- Commenting on pull requests to trigger Dependabot actions

A GitHub Actions workflow could be created to automate some of these steps, but would require:
- A workflow that triggers on successful completion of PR #295 CI
- Use of the GitHub API with appropriate permissions to merge and comment
- A bot token with write permissions

## Additional Information

- Dependabot PRs are updating GitHub Actions to their latest versions
- These updates bring Node 20 support and various bug fixes
- It's recommended to merge them after PR #295 to avoid conflicts
