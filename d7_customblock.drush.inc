<?php

/**
 * @file
 * Drush commands for D7 custom block module.
 */

/**
 * Implements hook_drush_command().
 */
function d7_customblock_drush_command() {
  $commands['d7_customblock_userinfo'] = array(
    'description' => 'Show info for a user',
    'aliases' => array('d7cu'),
    'arguments' => [
      'uid' => 'User ID.',
    ],
    'required-arguments' => TRUE,
    'options' => array(
      'roles' => 'Show roles.',
      'help' => 'Show command help.',
    ),
    'examples' => array(
      'drush d7cu --help' => 'Help.',
      'drush d7cu uid' => 'Print user info',
    ),
  );

  return $commands;
}

/**
 * Drush command logic.
 */
function drush_d7_customblock_userinfo($uid = '') {

  $option_roles = drush_get_option('roles', '0');
  $option_help = drush_get_option('help', '');

  $user = user_load($uid);

  if ($user === FALSE) {
    drush_log('User not exists', 'warning');
    if (drupal_is_cli()) {
      return;
    }
    exit;
  }

  if ($uid == 0) {
    $name = t('Anonimous user');
    $mail = '-';
  }
  else {
    $name = $user->name;
    $mail = $user->mail;
  }

  drush_print("> User info", 0);
  drush_print("Name: " . $name, 2);
  drush_print("Mail: " . $mail, 2);
  drush_print("Roles: " . implode(', ', $user->roles), 2);

}
