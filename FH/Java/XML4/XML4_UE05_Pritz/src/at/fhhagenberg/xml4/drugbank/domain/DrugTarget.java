package at.fhhagenberg.xml4.drugbank.domain;

import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class DrugTarget {
	
	private Drug drug;
	private TargetEntity targetEntity;
	private Set<String> actions = new HashSet<String>();
	private boolean targetWithKnownAction;

	public Drug getDrug() {
		return drug;
	}

	public void setDrug(Drug drug) {
		this.drug = drug;
	}

	public TargetEntity getTargetEntity() {
		return targetEntity;
	}

	public void setTargetEntity(TargetEntity targetEntity) {
		this.targetEntity = targetEntity;
	}

	public Set<String> getActions() {
		return actions;
	}

	public void setActions(Set<String> actions) {
		this.actions = actions;
	}

	public void addAction(String action) {
		this.actions.add(action);
	}

	public boolean isTargetWithKnownAction() {
		return targetWithKnownAction;
	}

	public void setTargetWithKnownAction(boolean targetWithKnownAction) {
		this.targetWithKnownAction = targetWithKnownAction;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		DrugTarget that = (DrugTarget) o;
		return Objects.equals(targetEntity.getAccession(), that.targetEntity.getAccession());
	}

	@Override
	public int hashCode() {
		return Objects.hash(targetEntity.getAccession());
	}
}
