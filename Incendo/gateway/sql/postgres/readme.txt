PostgreSQL scripts
------------------

recreate.cmd, recreate.sh - recreates (drops and then creates) oegw PostgreSQL database.
Prompts for 'postgres' user's password (if password-authentication is enabled)
to recreate 'oe' user.
Then prompts for created 'oe' user's password - use 'ingenico'.

all.sql is kind of SSO (single sign on) to execute all sql-scripts required.
This approach allows to avoid prompting user's password to execute every script.