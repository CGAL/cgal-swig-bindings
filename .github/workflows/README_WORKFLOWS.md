# GitHub Actions Workflows Documentation

## auto-refresh-dependabot.yml

### Purpose
Automatically refreshes (rebases) open Dependabot PRs when changes are pushed to the main branch.

### When it runs
- Automatically after any push to the `main` branch
- Can be manually triggered via "Actions" tab → "Auto-refresh Dependabot PRs" → "Run workflow"

### What it does
1. Fetches all open pull requests in the repository
2. Filters for PRs created by Dependabot with the "dependencies" label
3. Posts a `@dependabot rebase` comment on each PR to trigger a rebase
4. Adds a 2-second delay between each PR to avoid rate limiting

### Requirements
- The workflow requires the default `GITHUB_TOKEN` permissions
- The token must have permission to comment on issues/PRs (default for GitHub Actions)

### Usage
This workflow will automatically run after PR #295 is merged, refreshing all open Dependabot PRs.

You can also manually trigger it:
1. Go to the "Actions" tab in the repository
2. Select "Auto-refresh Dependabot PRs" from the workflows list
3. Click "Run workflow"
4. Select the "main" branch
5. Click "Run workflow"

### Manual Alternative
If you prefer to refresh Dependabot PRs manually, you can:
1. Navigate to each Dependabot PR
2. Add a comment: `@dependabot rebase`
3. Dependabot will automatically rebase the PR on the latest main branch

### Security Considerations
- This workflow only triggers on the main branch to prevent abuse
- It only affects PRs created by the Dependabot bot
- It only affects PRs with the "dependencies" label
- The workflow uses GitHub's built-in `github-script` action for safety

### Future Enhancements
Consider adding:
- Auto-approval for minor/patch version updates
- Auto-merge for PRs that pass all CI checks
- Notifications when PRs are refreshed
- Filtering by update type (major vs minor vs patch)
