<?php

/**
 * Implements hook_drush_help().
 */
function node_access_rebuild_drush_help($section) {
  switch ($section) {
    case 'drush:node-access-rebuild':
      return dt('Rebuild node access permissions.');
  }
}

function node_access_rebuild_drush_command() {
  $items = array();

  $items['node-access-rebuild'] = array(
    'description' => 'Rebuild the node access table',
    'callback' => 'drush_node_access_rebuild',
    'options' => array(),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'aliases' => array('nar'),
  );

  return $items;  
}

function drush_node_access_rebuild() {
  if (!drush_bootstrap_to_phase(DRUSH_BOOTSTRAP_DRUPAL_DATABASE)) {
    return drush_set_error('DRUPAL_SITE_NOT_FOUND', dt('You need to specify an alias or run this command within a drupal site.'));
  }
  if (count(module_implements('node_grants'))) {
    $batch = array(
      'title' => t('Rebuilding content access permissions'),
      'operations' => array(
        array('_node_access_rebuild_batch_operation', array()),
      ),
      'finished' => '_node_access_rebuild_batch_finished',
    );
    batch_set($batch);
    $batch =& batch_get();
    $batch['progressive'] = FALSE;
    drush_backend_batch_process();
  }
  if (!isset($batch)) {
    drupal_set_message(t('Content permissions have been rebuilt.'));
    node_access_needs_rebuild(FALSE);
    cache_clear_all();
  }
}

