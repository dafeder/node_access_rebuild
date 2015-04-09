# Drush Node Access Rebuild

Use drush to rebuild node access with a batch command.

Currently, the only way to rebuild node access with drush is `drush php-eval 'node_access_rebuild()'`, 
which will time out on a large database. By adding this command, you can use `drush node-access-rebuild` 
or `drush nar` to rebuild the permissions using drush's batch handling.

Unfortunately, there is currently no progressive output to let you know how much time is left.

To install, copy this directory inside of `~/.drush` and run `drush cc drush`. 
