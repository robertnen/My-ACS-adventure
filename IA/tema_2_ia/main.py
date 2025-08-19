import os
import warnings

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix, classification_report
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing import StandardScaler

from pathlib import Path

from scipy.stats import chi2_contingency

warnings.simplefilter(action='ignore', category=FutureWarning)

plt.style.use('default')
sns.set_palette("tab10")

def run_classification_analysis(filename, target_col):
    print(f"\n=== Clasificare pentru {filename} - tinta: {target_col} ===")
    df = pd.read_csv(f'results/preprocessed/{Path(filename).stem}_preprocessed.csv')

    if target_col not in df.columns:
        print(f"Coloana tinta '{target_col}' nu exista in fisierul preprocesat.")
        return

    #* formez x si y
    X = df.drop(columns=[target_col])
    y = df[target_col]

    #* daca e text, fac conversie
    if y.dtype == 'object':
        y = pd.factorize(y)[0]

    #* remove date-time format
    non_numeric_cols = X.select_dtypes(include=['object', 'datetime']).columns
    if len(non_numeric_cols) > 0:
        print(f"Se elimina coloanele non-numerice: {list(non_numeric_cols)}")
        X = X.drop(columns=non_numeric_cols)

    #* impart in train / test
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)

    classifiers = {
        'Logistic Regression': LogisticRegression(max_iter=1000),
        'Decision Tree': DecisionTreeClassifier(),
        'Random Forest': RandomForestClassifier(),
        'MLP (Neural Net)': MLPClassifier(max_iter=1000)
    }

    results = []

    for name, clf in classifiers.items():
        clf.fit(X_train, y_train)
        y_pred = clf.predict(X_test)

        acc = accuracy_score(y_test, y_pred)
        prec = precision_score(y_test, y_pred, average='weighted', zero_division=0)
        rec = recall_score(y_test, y_pred, average='weighted', zero_division=0)
        f1 = f1_score(y_test, y_pred, average='weighted', zero_division=0)

        results.append({
            'Classifier': name,
            'Accuracy': acc,
            'Precision': prec,
            'Recall': rec,
            'F1-score': f1
        })

        print(f"\n--- {name} ---")
        print(classification_report(y_test, y_pred, zero_division=0))

        #* matrice confuzie
        cm = confusion_matrix(y_test, y_pred)
        plt.figure(figsize=(6, 5))
        sns.heatmap(cm, annot=True, fmt='d', cmap='Blues')
        plt.title(f'Confusion Matrix - {name}')
        plt.xlabel('Predicted')
        plt.ylabel('Actual')
        plt.tight_layout()
        plt.savefig(f'results/plots/{Path(filename).stem}_{name.replace(" ", "_")}_confusion_matrix.png')
        plt.close()

    #* tabel comparativ
    results_df = pd.DataFrame(results).round(4)
    print("\n=== Rezultate comparative ===")
    print(results_df)

    results_df.to_csv(f'results/tables/{Path(filename).stem}_classification_results.csv', index=False)
    print(f"Rezultate salvate in results/tables/{Path(filename).stem}_classification_results.csv")

def create_output_dirs():
    dirs = [
        'results/tables',
        'results/plots',
        'results/correlation',
        'results/outliers',
        'results/preprocessed'
    ]
    for d in dirs:
        os.makedirs(d, exist_ok=True)


#* incarca datele cu tratament pentru valori lipsa
def load_data(filename):
    return pd.read_csv(filename, na_values=['', ' ', 'NaN', 'nan'])


def detect_outliers_iqr(df, col, q1=0.25, q3=0.75):
    Q1 = df[col].quantile(q1)
    Q3 = df[col].quantile(q3)
    IQR = Q3 - Q1
    lower = Q1 - 1.5 * IQR
    upper = Q3 + 1.5 * IQR
    outliers = df[(df[col] < lower) | (df[col] > upper)]
    return outliers, lower, upper

def preprocess_data(df, filename, target_col=None):
    print(f"\n--- Preprocesare date pentru {filename} ---")

    #* inlocuire extreme numerice cu nan, fara coloana tinta
    numeric_cols = df.select_dtypes(include=[np.number]).columns.tolist()
    if target_col in numeric_cols:
        numeric_cols.remove(target_col)

    for col in numeric_cols:
        if df[col].notna().sum() > 0:
            Q1 = df[col].quantile(0.25)
            Q3 = df[col].quantile(0.75)
            IQR = Q3 - Q1
            lower = Q1 - 1.5 * IQR
            upper = Q3 + 1.5 * IQR
            outlier_mask = (df[col] < lower) | (df[col] > upper)
            n_outliers = outlier_mask.sum()
            df.loc[outlier_mask, col] = np.nan
            print(f"Coloana '{col}': {n_outliers} valori outlier inlocuite cu NaN")

    #* imputare ignorand coloana tinta
    for col in numeric_cols:
        median = df[col].median()
        n_missing_before = df[col].isna().sum()
        df[col].fillna(median, inplace=True)
        n_missing_after = df[col].isna().sum()
        if n_missing_before > 0:
            print(f"Coloana '{col}': imputate {n_missing_before - n_missing_after} valori lipsa cu mediana ({median})")

    #* imputare pe toate, inclusiv target_col daca este categorial
    categoric_cols = df.select_dtypes(exclude=[np.number]).columns.tolist()
    if target_col in categoric_cols:
        categoric_cols.remove(target_col)

    for col in categoric_cols:
        mode = df[col].mode()
        if not mode.empty:
            mode_val = mode[0]
            n_missing_before = df[col].isna().sum()
            df[col].fillna(mode_val, inplace=True)
            n_missing_after = df[col].isna().sum()
            if n_missing_before > 0:
                print(f"Coloana '{col}': imputate {n_missing_before - n_missing_after} valori lipsa cu moda ('{mode_val}')")

    #* eliminare coloane redundante (corelatie > 0.95), fara target_col
    corr_matrix = df[numeric_cols].corr().abs()
    upper_tri = corr_matrix.where(np.triu(np.ones(corr_matrix.shape), k=1).astype(bool))
    to_drop = [col for col in upper_tri.columns if any(upper_tri[col] > 0.95)]
    if to_drop:
        print(f"Elimin coloane numeric redundante (corelatie > 0.95): {to_drop}")
        df.drop(columns=to_drop, inplace=True)
    else:
        print("Nu s-au gasit coloane numeric redundante de eliminat.")

    #* standardizare numerica, ignorand target_col
    numeric_cols_after = df.select_dtypes(include=[np.number]).columns.tolist()
    if target_col in numeric_cols_after:
        numeric_cols_after.remove(target_col)

    scaler = StandardScaler()
    df[numeric_cols_after] = scaler.fit_transform(df[numeric_cols_after])
    print(f"Standardizare aplicata pe coloanele numerice: {numeric_cols_after}")

    #* salveaza datele
    df.to_csv(f'results/preprocessed/{Path(filename).stem}_preprocessed.csv', index=False)
    print(f"Datele preprocesate au fost salvate in results/preprocessed/{Path(filename).stem}_preprocessed.csv")

    return df


def analyze_numeric(df, filename):
    numeric_cols = df.select_dtypes(include=[np.number]).columns.tolist()
    if not numeric_cols:
        return

    messages = [f"\n--- Analiza numerica ---"]

    stats = df[numeric_cols].describe().round(2)
    stats.loc['count_non_null'] = df[numeric_cols].count()
    stats.loc['missing_values'] = df[numeric_cols].isna().sum()
    stats = stats.reindex(['count_non_null', 'missing_values', 'mean', 'std', 'min', '25%', '50%', '75%', 'max'])
    stats.to_csv(f'results/tables/{Path(filename).stem}_numeric_stats.csv')
    messages.append(f"Statistici numerice salvate in results/tables/{Path(filename).stem}_numeric_stats.csv")

    if len(numeric_cols) > 1:
        corr = df[numeric_cols].corr(method='pearson')
        corr.to_csv(f'results/correlation/{Path(filename).stem}_correlation_matrix.csv')

        plt.figure(figsize=(14, 12))
        sns.heatmap(corr, annot=True, cmap='coolwarm', center=0, square=True, cbar_kws={"shrink": .8}, fmt='.2f')
        plt.title(f'Matrice corelatie completa: {Path(filename).stem}', fontsize=16, pad=20)
        plt.tight_layout()
        plt.savefig(f'results/correlation/{Path(filename).stem}_correlation_heatmap.png', dpi=300, bbox_inches='tight')
        plt.close()
        messages.append(f"Matrice corelatie completa salvata in results/correlation/{Path(filename).stem}_correlation_heatmap.png")

    outlier_summary = {}
    for col in numeric_cols:
        if df[col].notna().sum() > 0:
            outliers, low, high = detect_outliers_iqr(df, col)
            outlier_summary[col] = {
                'outliers_count': len(outliers),
                'outliers_percentage': (len(outliers) / len(df)) * 100,
                'lower_bound': low,
                'upper_bound': high
            }
    pd.DataFrame(outlier_summary).T.to_csv(f'results/outliers/{Path(filename).stem}_outliers_analysis.csv')
    messages.append(f"Analiza outliers salvata in results/outliers/{Path(filename).stem}_outliers_analysis.csv")

    #* boxplot pentru primele 12 coloane
    cols_to_plot = numeric_cols[:12]
    n_rows = (len(cols_to_plot) + 2) // 3
    fig, axes = plt.subplots(n_rows, 3, figsize=(15, 5 * n_rows))
    axes = axes.flatten()
    for i, col in enumerate(cols_to_plot):
        df.boxplot(column=col, ax=axes[i])
        axes[i].set_title(col)
        axes[i].tick_params(axis='x', rotation=45)
    for j in range(i + 1, len(axes)):
        axes[j].set_visible(False)
    plt.tight_layout()
    plt.savefig(f'results/plots/{Path(filename).stem}_boxplots.png', dpi=300, bbox_inches='tight')
    plt.close()
    messages.append(f"Boxplot-uri individuale salvate in results/plots/{Path(filename).stem}_boxplots.png")

    #* boxplot combinat pentru primele 10 coloane
    if cols_to_plot:
        plt.figure(figsize=(12, 6))
        sns.boxplot(data=df[cols_to_plot])
        plt.xticks(rotation=45)
        plt.title(f'Boxplot combinat: {Path(filename).stem}')
        plt.tight_layout()
        plt.savefig(f'results/plots/{Path(filename).stem}_boxplot_combined.png', dpi=300, bbox_inches='tight')
        plt.close()
        messages.append(f"Boxplot combinat salvat in results/plots/{Path(filename).stem}_boxplot_combined.png")

    print('\n'.join(messages))


def analyze_categorical(df, filename):
    categoric_cols = df.select_dtypes(exclude=[np.number]).columns.tolist()
    if not categoric_cols:
        return

    messages = [f"\n--- Analiza categorica ---"]

    stats = pd.DataFrame({
        'count_non_null': df[categoric_cols].count(),
        'missing_values': df[categoric_cols].isna().sum(),
        'unique_values': df[categoric_cols].nunique()
    })

    for col in categoric_cols:
        sample = df[col].dropna().unique()[:5]
        stats.loc[col, 'sample_values'] = str(sample)

    stats.to_csv(f'results/tables/{Path(filename).stem}_categoric_stats.csv')
    messages.append(f"Statistici categorice salvate in results/tables/{Path(filename).stem}_categoric_stats.csv")

    if len(categoric_cols) > 1:
        chi_results = {}
        pairs = [(categoric_cols[i], categoric_cols[j])
                    for i in range(len(categoric_cols))
                    for j in range(i + 1, len(categoric_cols))]
        for col1, col2 in pairs[:10]:
            subset = df[[col1, col2]].dropna()
            if len(subset) > 10:
                try:
                    contingency = pd.crosstab(subset[col1], subset[col2])
                    chi2, p, dof, exp = chi2_contingency(contingency)
                    chi_results[f"{col1}_vs_{col2}"] = {'chi2': chi2, 'p_value': p, 'significant': p < 0.05}
                except Exception as e:
                    chi_results[f"{col1}_vs_{col2}"] = {'error': str(e)}

        if chi_results:
            chi_df = pd.DataFrame([{
                'pair': k,
                'chi2_statistic': v.get('chi2', 'N/A'),
                'p_value': v.get('p_value', 'N/A'),
                'significant': v.get('significant', False)}
                    for k, v in chi_results.items()
            ])
            chi_df.to_csv(f'results/correlation/{Path(filename).stem}_chi_square_results.csv', index=False)
            messages.append(f"Rezultate test chi-square salvate in results/correlation/{Path(filename).stem}_chi_square_results.csv")

    print('\n'.join(messages))


def analyze_class_distribution(df, target_cols, filename, max_categories=35):
    for col in target_cols:
        if col not in df.columns:
            continue

        counts = df[col].value_counts()
        percentages = df[col].value_counts(normalize=True) * 100

        header_msg = (
            f"\nDistributia pentru coloana '{col}':\n"
            f"Numar clase unice: {len(counts)}\n"
            f"{counts.head(max_categories)}"
        )
        print(header_msg)

        distrib_df = pd.DataFrame({
            'class': counts.index[:max_categories],
            'count': counts.values[:max_categories],
            'percentage': percentages[counts.index[:max_categories]].round(2)
        })
        distrib_df.to_csv(f'results/tables/{Path(filename).stem}_{col}_class_distribution.csv', index=False)

        plt.figure(figsize=(8, 5))
        bars = plt.bar(distrib_df['class'].astype(str), distrib_df['count'], color='cornflowerblue', edgecolor='black')
        plt.title(f'Distributia clasei pentru "{col}"')
        plt.xlabel('Clase')
        plt.ylabel('Numar aparitii')
        plt.xticks(rotation=45, ha='right')

        for bar in bars:
            plt.text(bar.get_x() + bar.get_width()/2, bar.get_height(), f'{int(bar.get_height())}',
                    ha='center', va='bottom', fontsize=9)

        plt.tight_layout()
        plt.savefig(f'results/plots/{Path(filename).stem}_{col}_class_distribution.png', dpi=300)
        plt.close()
        print(f"Grafic distributie salvat in results/plots/{Path(filename).stem}_{col}_class_distribution.png")


def analyze_dataset(filename, target_col):
    header_msg = f"\n=== Analizez {filename} ==="
    df = load_data(filename)
    df = preprocess_data(df, filename, target_col=target_col)
    shape_msg = f"Shape: {df.shape}"
    missing_msg = f"Valori lipsa total: {df.isna().sum().sum()}"

    numeric_cols = df.select_dtypes(include=[np.number]).columns.tolist()
    categoric_cols = df.select_dtypes(exclude=[np.number]).columns.tolist()
    possible_targets = ['Class', 'Target', 'Overall AQI Level', 'Overall AQI']
    target_cols = [col for col in possible_targets if col in df.columns]

    cols_msg = (
        f"Coloane numerice: {len(numeric_cols)}\n"
        f"Coloane categorice: {len(categoric_cols)}\n"
        f"Coloane target identificate: {target_cols}"
    )

    print('\n'.join([header_msg, shape_msg, missing_msg, cols_msg]))

    analyze_numeric(df, filename)
    analyze_categorical(df, filename)
    if target_cols:
        analyze_class_distribution(df, target_cols, filename)

    print(f"\n=== Sfarsit analiza pentru {filename} ===")


if __name__ == '__main__':
    create_output_dirs()

    files = [
        ('pirvision_full.csv', 'Class'),
        ('air_pollution2_full.csv', 'Overall AQI Level')
    ]

    for file, target in files:
        analyze_dataset(file, target)  #? 3.1 + 3.2
        run_classification_analysis(file, target)  #? 3.3
