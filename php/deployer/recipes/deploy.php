<?php
namespace Deployer;

require 'recipe/common.php';

// Project name
set('application', 'my_project');

// Project repository
set('repository', 'https://github.com/jonipievilainen/react-training');

// [Optional] Allocate tty for git clone. Default value is false.
set('git_tty', true); 

// Shared files/dirs between deploys 
set('shared_files', []);
set('shared_dirs', []);

// Writable dirs by web server 
set('writable_dirs', []);

set('branch', 'master');

set('default_stage', 'production');

// Hosts
localhost()
    ->stage('production')
    ->set('deploy_path', '/var/www/html/live_deployer/versions/');


// Tasks
task('test', [
    'deploy:release',
    'deploy:update_code',
    'checkDiff',
]);

task('checkDiff', function () {
    run('mkdir -p log');
    
    $releaseDir = run('ls -d -td -- $PWD/versions/releases/*/ | head -n 1');
    $liveDir = '/var/www/html/live/';
    // $command = "git diff ".$liveDir." ".$releaseDir." > log/".time().".log"; // ." > log/".time().".log"
    $command = "diff -r --exclude='.git' ".$liveDir." ".$releaseDir." > log/".time().".log";

    writeln($command);

    run($command);
});


desc('Deploy your project');
task('deploy', [
    'deploy:info',
    'deploy:prepare',
    'deploy:lock',
    'deploy:release',
    'deploy:update_code',
    'checkDiff', // TODO: some error handle needed
    'deploy:shared',
    'deploy:writable',
    'deploy:vendors',
    'deploy:clear_paths',
    'deploy:symlink',
    'deploy:unlock',
    'cleanup',
    'success'
]);

task('undo', function () {
    writeln('Undo last release');
});

// [Optional] If deploy fails automatically unlock.
after('deploy:failed', 'deploy:unlock');
