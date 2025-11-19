pipeline {
    agent any

    environment {
        SONARCLOUD_URL = "https://sonarcloud.io"
        ORG = "mightykarim"
        PROJECT = "Static-3"
    }

    stages {

        stage('Checkout') {
            steps {
                git branch: 'main', url: 'https://github.com/mightykarim/Static-3.git'
            }
        }

        stage('Build') {
            steps {
                echo "Build step..."
            }
        }

        stage('Upload to SonarCloud') {
            steps {
                withCredentials([string(credentialsId: 'SONAR_CLOUD_TOKEN', variable: 'TOKEN')]) {
                    bat """
                        powershell Compress-Archive -Path * -DestinationPath project.zip
                        curl -X POST "https://sonarcloud.io/api/scanner/scan" ^
                            -H "Authorization: Bearer %TOKEN%" ^
                            -F "projectKey=Static-3" ^
                            -F "organization=mightykarim" ^
                            -F "code=@project.zip"
                    """
                }
            }
        }


        stage('Quality Gate Check') {
            steps {
                script {
                    echo "Checking Quality Gate..."
                    timeout(time: 60, unit: 'SECONDS') {
                        def status = bat(
                            script: """
                                curl -s -H "Authorization: Bearer %TOKEN%" "%SONARCLOUD_URL%/api/qualitygates/project_status?projectKey=%PROJECT%"
                            """,
                            returnStdout: true
                        ).trim()
                        echo "Response: ${status}"

                        if (status.contains('"status":"ERROR"')) {
                            error("❌ Quality Gate Failed")
                        } else {
                            echo "✅ Quality Gate Passed"
                        }
                    }
                }
            }
        }

        stage('Deploy') {
            steps {
                echo "Done — Deployment stage"
            }
        }
    }
}
