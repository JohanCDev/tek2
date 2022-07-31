folder("/Tools") {
  description("Folder for miscellaneous tools.")
}

freeStyleJob('/Tools/clone-repository') {
  parameters {
    stringParam('GIT_REPOSITORY_URL', null, 'Git URL of the repository to clone')
  }
  steps {
    wrappers {
      preBuildCleanup {
        cleanupParameter('Cleanup')
      }
    }
    shell('git clone $GIT_REPOSITORY_URL')
  }
}

freeStyleJob('/Tools/SEED') {
  parameters {
    stringParam('GITHUB_NAME', null, 'GitHub repository owner/repo_name (e.g.: "EpitechIT31000/chocolatine")')
    stringParam('DISPLAY_NAME', null, 'Display name for the job')
  }
  steps {
    jobDsl {
      scriptText('''
      job("/\${DISPLAY_NAME}") {
        scm {
          github("\${GITHUB_NAME}")
          triggers {
            scm("* * * * *")
          }
        }
        wrappers {
          preBuildCleanup {
            cleanupParameter('Cleanup')
          }
        }
        steps {
          shell("make fclean")
          shell("make")
          shell("make tests_run")
          shell("make clean")
        }
      }'''.stripIndent())
    }
  }
}

import javaposse.jobdsl.plugin.GlobalJobDslSecurityConfiguration
import jenkins.model.GlobalConfiguration

GlobalConfiguration.all().get(GlobalJobDslSecurityConfiguration.class).useScriptSecurity=false